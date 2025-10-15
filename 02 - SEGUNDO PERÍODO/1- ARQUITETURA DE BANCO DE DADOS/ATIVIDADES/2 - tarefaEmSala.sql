CREATE TABLE ALUNO (
	id_aluno int not null primary key,
	nome varchar(50)
);
create table nota(
	id_nota int not null primary key,
	id_aluno int, FOREIGN KEY (id_aluno) REFERENCES ALUNO(id_aluno)
);

INSERT INTO ALUNO (id_aluno, nome) VALUES
(1, 'Ana'),
(2, 'Bruno'),
(3, 'Carla'),
(4, 'Daniel'),
(5, 'Eva');
INSERT INTO nota (id_nota, id_aluno) VALUES
(101, 1),
(102, 3),
(103, 5);
