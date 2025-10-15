-- Exercício 1:
SELECT nome, cidade FROM aluno ORDER BY nome;

-- Exercício 2:
SELECT nome_curso FROM curso WHERE carga_horaria > 40;

-- Exercício 3:
SELECT nome FROM professor WHERE especialidade LIKE '%Exatas%';

-- Exercício 4:
SELECT COUNT(*) FROM aluno WHERE YEAR(data_nascimento) > 2005;

-- Exercício 5:
SELECT nome, matricula, TIMESTAMPDIFF(YEAR, data_nascimento, CURDATE()) AS idade FROM aluno ORDER BY idade DESC;

-- Exercício 6:
SELECT t.nome_turma, c.nome_curso, p.nome AS nome_professor
FROM turma t
JOIN curso c ON t.id_curso = c.id
JOIN professor p ON t.id_professor = p.id;

-- Exercício 7:
SELECT a.nome
FROM aluno a
JOIN matricula m ON a.id = m.id_aluno
JOIN turma t ON m.id_turma = t.id
JOIN curso c ON t.id_curso = c.id
WHERE c.nome_curso = 'Matemática';

-- Exercício 8:
SELECT c.nome_curso, COUNT(m.id_aluno) AS quantidade_alunos
FROM curso c
JOIN turma t ON c.id = t.id_curso
JOIN matricula m ON t.id = m.id_turma
GROUP BY c.nome_curso
ORDER BY quantidade_alunos DESC;

-- Exercício 9:
SELECT nome FROM aluno WHERE id NOT IN (SELECT id_aluno FROM matricula WHERE status = 'Ativa');

-- Exercício 10:
SELECT a.nome
FROM aluno a
JOIN matricula m ON a.id = m.id_aluno
JOIN turma t ON m.id_turma = t.id
JOIN curso c ON t.id_curso = c.id
WHERE c.nome_curso = 'Física'
GROUP BY a.id, a.nome
HAVING COUNT(DISTINCT t.id) = (SELECT COUNT(*) FROM turma t2 JOIN curso c2 ON t2.id_curso = c2.id WHERE c2.nome_curso = 'Física');

-- Exercício 11:
SELECT p.nome, COUNT(t.id) AS quantidade_turmas
FROM professor p
JOIN turma t ON p.id = t.id_professor
GROUP BY p.id, p.nome
HAVING COUNT(t.id) > 1;

-- Exercício 12:
SELECT cidade, COUNT(id) AS quantidade_alunos
FROM aluno
GROUP BY cidade
ORDER BY quantidade_alunos DESC;

-- Exercício 13:
SELECT c.nome_curso
FROM curso c
LEFT JOIN turma t ON c.id = t.id_curso
WHERE t.id IS NULL;

-- Exercício 14:
SELECT a.nome, a.matricula
FROM aluno a
JOIN matricula m ON a.id = m.id_aluno
WHERE m.status = 'Ativa'
GROUP BY a.id, a.nome, a.matricula
HAVING COUNT(m.id_turma) > 1;

-- Exercício 15:
SELECT t.nome_turma, AVG(TIMESTAMPDIFF(YEAR, a.data_nascimento, CURDATE())) AS media_idade
FROM turma t
JOIN matricula m ON t.id = m.id_turma
JOIN aluno a ON m.id_aluno = a.id
WHERE m.status = 'Ativa'
GROUP BY t.id, t.nome_turma;

-- exercício 16:
WITH TurmaAlunos AS (
    SELECT
        t.id AS id_turma,
        t.id_curso,
        COUNT(m.id_aluno) AS total_alunos
    FROM turma t
    JOIN matricula m ON t.id = m.id_turma
    WHERE m.status = 'Ativa'
    GROUP BY t.id, t.id_curso
),

RankingTurmas AS (
    SELECT
        id_curso,
        id_turma,
        RANK() OVER (PARTITION BY id_curso ORDER BY total_alunos DESC) as ranking
    FROM TurmaAlunos
)

SELECT c.nome_curso, p.nome AS nome_professor
FROM RankingTurmas rt
JOIN turma t ON rt.id_turma = t.id
JOIN curso c ON rt.id_curso = c.id
JOIN professor p ON t.id_professor = p.id
WHERE rt.ranking = 1;

-- Exercício 17:
SELECT a.nome, COUNT(DISTINCT c.id) AS quantidade_cursos
FROM aluno a
JOIN matricula m ON a.id = m.id_aluno
JOIN turma t ON m.id_turma = t.id
JOIN curso c ON t.id_curso = c.id
GROUP BY a.id, a.nome;

-- exercício 18:
SELECT t.nome_turma
FROM turma t
LEFT JOIN matricula m ON t.id = m.id_turma AND m.status = 'Ativa'
WHERE m.id_aluno IS NULL;

-- Exercício 19:
SELECT p.nome
FROM professor p
JOIN turma t ON p.id = t.id_professor
GROUP BY p.id, p.nome
HAVING COUNT(DISTINCT t.id_curso) > 1;

-- Exercício 20:
SELECT a.nome
FROM aluno a
JOIN matricula m ON a.id = m.id_aluno
JOIN turma t ON m.id_turma = t.id
JOIN curso c ON t.id_curso = c.id
WHERE m.status = 'Ativa' AND c.nome_curso IN ('Biologia', 'Matemática')
GROUP BY a.id, a.nome
HAVING COUNT(DISTINCT c.nome_curso) = 2;
