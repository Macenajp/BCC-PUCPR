-- Dump do banco de dados "escola_complexa"
-- -----------------------------------------------------

DROP DATABASE IF EXISTS escola_complexa;
CREATE DATABASE escola_complexa;
USE escola_complexa;

-- -----------------------------------------------------
-- Tabela: aluno
-- -----------------------------------------------------
CREATE TABLE aluno (
    id INT AUTO_INCREMENT,
    nome VARCHAR(100) NOT NULL,
    matricula VARCHAR(20) UNIQUE NOT NULL,
    data_nascimento DATE NOT NULL,
    cidade VARCHAR(50) NOT NULL,
    email VARCHAR(100),
    PRIMARY KEY (id)
);

-- -----------------------------------------------------
-- Tabela: professor
-- -----------------------------------------------------
CREATE TABLE professor (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    especialidade VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE
);

-- -----------------------------------------------------
-- Tabela: curso
-- -----------------------------------------------------
CREATE TABLE curso (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome_curso VARCHAR(100) NOT NULL UNIQUE,
    carga_horaria INT NOT NULL,
    nivel ENUM('Básico','Intermediário','Avançado') DEFAULT 'Básico',
    CONSTRAINT chk_carga CHECK (carga_horaria > 10)
);

-- -----------------------------------------------------
-- Tabela: turma
-- -----------------------------------------------------
CREATE TABLE turma (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome_turma VARCHAR(100) NOT NULL,
    id_curso INT NOT NULL,
    id_professor INT NOT NULL,
    semestre YEAR NOT NULL,
    turno ENUM('Manhã','Tarde','Noite') NOT NULL,
    FOREIGN KEY (id_curso) REFERENCES curso(id),
    FOREIGN KEY (id_professor) REFERENCES professor(id)
);

-- -----------------------------------------------------
-- Tabela intermediária: disciplina (exemplo de N:N entre curso e professor)
-- -----------------------------------------------------
CREATE TABLE disciplina (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome_disciplina VARCHAR(100) NOT NULL,
    id_curso INT NOT NULL,
    FOREIGN KEY (id_curso) REFERENCES curso(id)
);

CREATE TABLE professor_disciplina (
    id_professor INT,
    id_disciplina INT,
    PRIMARY KEY (id_professor, id_disciplina),
    FOREIGN KEY (id_professor) REFERENCES professor(id),
    FOREIGN KEY (id_disciplina) REFERENCES disciplina(id)
);

-- -----------------------------------------------------
-- Tabela: matricula
-- -----------------------------------------------------
CREATE TABLE matricula (
    id INT AUTO_INCREMENT PRIMARY KEY,
    id_aluno INT NOT NULL,
    id_turma INT NOT NULL,
    data_matricula DATE NOT NULL,
    status ENUM('Ativa','Inativa','Cancelada') NOT NULL DEFAULT 'Ativa',
    nota_final DECIMAL(4,2),
    UNIQUE (id_aluno, id_turma),
    FOREIGN KEY (id_aluno) REFERENCES aluno(id),
    FOREIGN KEY (id_turma) REFERENCES turma(id)
);

-- -----------------------------------------------------
-- VIEW: Relatório de alunos ativos por curso
-- -----------------------------------------------------
CREATE VIEW vw_alunos_por_curso AS
SELECT c.nome_curso, COUNT(m.id) AS qtd_alunos
FROM curso c
LEFT JOIN turma t ON c.id = t.id_curso
LEFT JOIN matricula m ON t.id = m.id_turma AND m.status = 'Ativa'
GROUP BY c.nome_curso;

-- -----------------------------------------------------
-- TRIGGER: Atualizar status automaticamente se a nota final for < 6
-- -----------------------------------------------------
DELIMITER //
CREATE TRIGGER trg_atualiza_status
BEFORE UPDATE ON matricula
FOR EACH ROW
BEGIN
    IF NEW.nota_final IS NOT NULL AND NEW.nota_final < 6 THEN
        SET NEW.status = 'Inativa';
    END IF;
END;
//
DELIMITER ;

-- -----------------------------------------------------
-- PROCEDURE: Listar alunos por cidade
-- -----------------------------------------------------
DELIMITER //
CREATE PROCEDURE sp_alunos_por_cidade(IN cidade_nome VARCHAR(50))
BEGIN
    SELECT nome, matricula, data_nascimento
    FROM aluno
    WHERE cidade = cidade_nome;
END;
//
DELIMITER ;

-- -----------------------------------------------------
-- Inserts
-- -----------------------------------------------------

-- Alunos
INSERT INTO aluno (nome, matricula, data_nascimento, cidade, email) VALUES
('Ana Silva', 'A001', '2004-05-10', 'Curitiba', 'ana.silva@email.com'),
('Bruno Costa', 'A002', '2006-08-15', 'Londrina', 'bruno.costa@email.com'),
('Carlos Mendes', 'A003', '2003-11-20', 'Curitiba', NULL),
('Daniela Rocha', 'A004', '2007-01-12', 'Maringá', 'daniela.rocha@email.com');

-- Professores
INSERT INTO professor (nome, especialidade, email) VALUES
('Marcos Pires', 'Exatas - Matemática', 'marcos@escola.com'),
('Luciana Teixeira', 'Exatas - Física', 'luciana@escola.com'),
('Paulo Oliveira', 'Biologia', 'paulo@escola.com');

-- Cursos
INSERT INTO curso (nome_curso, carga_horaria, nivel) VALUES
('Matemática', 80, 'Avançado'),
('Física', 60, 'Intermediário'),
('Biologia', 40, 'Básico');

-- Disciplinas
INSERT INTO disciplina (nome_disciplina, id_curso) VALUES
('Cálculo I', 1),
('Álgebra Linear', 1),
('Mecânica Clássica', 2),
('Genética', 3);

-- Ligação Professor ↔ Disciplina
INSERT INTO professor_disciplina VALUES
(1,1),(1,2),(2,3),(3,4);

-- Turmas
INSERT INTO turma (nome_turma, id_curso, id_professor, semestre, turno) VALUES
('Matemática A', 1, 1, 2024, 'Manhã'),
('Física B', 2, 2, 2024, 'Noite'),
('Biologia C', 3, 3, 2024, 'Tarde');

-- Matrículas
INSERT INTO matricula (id_aluno, id_turma, data_matricula, status, nota_final) VALUES
(1,1,'2024-02-01','Ativa',8.5),
(2,1,'2024-02-02','Ativa',5.5),
(3,2,'2024-02-03','Ativa',7.0),
(4,3,'2024-02-04','Ativa',NULL);
