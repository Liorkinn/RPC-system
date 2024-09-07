--
-- PostgreSQL database dump
--

-- Dumped from database version 12.20 (Ubuntu 12.20-0ubuntu0.20.04.1)
-- Dumped by pg_dump version 12.20 (Ubuntu 12.20-0ubuntu0.20.04.1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: postgres; Type: DATABASE; Schema: -; Owner: postgres
--

CREATE DATABASE postgres WITH TEMPLATE = template0 ENCODING = 'UTF8' LC_COLLATE = 'en_US.UTF-8' LC_CTYPE = 'en_US.UTF-8';


ALTER DATABASE postgres OWNER TO postgres;

\connect postgres

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: DATABASE postgres; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON DATABASE postgres IS 'default administrative connection database';


--
-- Name: rec; Type: SCHEMA; Schema: -; Owner: postgres
--

CREATE SCHEMA rec;


ALTER SCHEMA rec OWNER TO postgres;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: access_level; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.access_level (
    id integer NOT NULL,
    type_role integer,
    role_name text
);


ALTER TABLE public.access_level OWNER TO postgres;

--
-- Name: TABLE access_level; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE public.access_level IS 'Уровни доступа пользователей';


--
-- Name: access_level_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.access_level_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.access_level_id_seq OWNER TO postgres;

--
-- Name: access_level_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.access_level_id_seq OWNED BY public.access_level.id;


--
-- Name: component_options; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.component_options (
    id integer NOT NULL,
    component_id integer NOT NULL,
    option_name character varying(100) NOT NULL,
    option_description text
);


ALTER TABLE public.component_options OWNER TO postgres;

--
-- Name: component_options_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.component_options_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.component_options_id_seq OWNER TO postgres;

--
-- Name: component_options_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.component_options_id_seq OWNED BY public.component_options.id;


--
-- Name: components; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.components (
    id integer NOT NULL,
    name character varying(100) NOT NULL,
    description text
);


ALTER TABLE public.components OWNER TO postgres;

--
-- Name: components_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.components_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.components_id_seq OWNER TO postgres;

--
-- Name: components_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.components_id_seq OWNED BY public.components.id;


--
-- Name: computer_component_options; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.computer_component_options (
    id integer NOT NULL,
    computer_id integer NOT NULL,
    component_option_id integer NOT NULL
);


ALTER TABLE public.computer_component_options OWNER TO postgres;

--
-- Name: computer_component_options_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.computer_component_options_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.computer_component_options_id_seq OWNER TO postgres;

--
-- Name: computer_component_options_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.computer_component_options_id_seq OWNED BY public.computer_component_options.id;


--
-- Name: computers; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.computers (
    id integer NOT NULL,
    name character varying(100) NOT NULL,
    description text,
    image_path character varying(255)
);


ALTER TABLE public.computers OWNER TO postgres;

--
-- Name: computers_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.computers_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.computers_id_seq OWNER TO postgres;

--
-- Name: computers_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.computers_id_seq OWNED BY public.computers.id;


--
-- Name: users; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.users (
    id integer NOT NULL,
    name text,
    surname text,
    patronymic text,
    age integer,
    telephone text,
    login text,
    password text,
    access_level_id integer
);


ALTER TABLE public.users OWNER TO postgres;

--
-- Name: users_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

ALTER TABLE public.users ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.users_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- Name: access_level id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.access_level ALTER COLUMN id SET DEFAULT nextval('public.access_level_id_seq'::regclass);


--
-- Name: component_options id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.component_options ALTER COLUMN id SET DEFAULT nextval('public.component_options_id_seq'::regclass);


--
-- Name: components id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.components ALTER COLUMN id SET DEFAULT nextval('public.components_id_seq'::regclass);


--
-- Name: computer_component_options id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.computer_component_options ALTER COLUMN id SET DEFAULT nextval('public.computer_component_options_id_seq'::regclass);


--
-- Name: computers id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.computers ALTER COLUMN id SET DEFAULT nextval('public.computers_id_seq'::regclass);


--
-- Data for Name: access_level; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.access_level (id, type_role, role_name) FROM stdin;
1	1	Пациент
2	2	Доктор
\.


--
-- Data for Name: component_options; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.component_options (id, component_id, option_name, option_description) FROM stdin;
1	1	Intel Core i5	2.5 GHz, 6 cores
2	1	AMD Ryzen 5	3.2 GHz, 8 cores
3	2	8 GB	DDR4, 2400 MHz
4	2	16 GB	DDR4, 3200 MHz
5	3	NVIDIA GeForce GTX 1660	6 GB GDDR6, 1408 CUDA cores
6	3	AMD Radeon RX 560X	4 GB GDDR5, 1280 Stream processors
7	4	512 GB SSD	SATA III, 500 MB/s read, 450 MB/s write
8	4	1 TB HDD	7200 RPM, 128 MB cache
9	1	Intel Core i7	3.5 GHz, 8 cores
10	1	Intel Core i7-4f	4.0 GHz, 12 cores
11	1	AMD Ryzen 7	4.5 GHz, 16 cores
12	3	NVIDIA GeForce GTX 1660 TI	8 GB GDDR6, 1408 CUDA cores
13	3	NVIDIA GeForce GTX 3060	12 GB GDDR6, 1408 CUDA cores
14	3	NVIDIA GeForce GTX 4060	12 GB GDDR6, 3000 CUDA cores
15	3	NVIDIA GeForce GTX 4070 TI	16 GB GDDR6, 4500 CUDA cores
16	5	Aerocool Max	Arocool, 700Вт
17	5	Xas Max	Xas, 900Вт
18	5	DeepCool Mini	DeepCool, 500Вт
\.


--
-- Data for Name: components; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.components (id, name, description) FROM stdin;
1	CPU	Central Processing Unit
2	RAM	Random Access Memory
3	GPU	Graphics Processing Unit
4	Storage	Hard Drive or Solid State Drive
5	BP	Block power
\.


--
-- Data for Name: computer_component_options; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.computer_component_options (id, computer_id, component_option_id) FROM stdin;
1	1	1
2	1	3
3	1	7
4	2	2
5	2	4
6	2	8
7	3	5
8	3	6
9	4	1
10	4	3
11	1	18
12	1	14
13	5	1
14	5	3
15	5	6
16	5	8
17	5	17
18	6	1
19	6	3
20	6	6
21	6	8
22	6	17
\.


--
-- Data for Name: computers; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.computers (id, name, description, image_path) FROM stdin;
1	Dell Inspiron 15 5000	15.6" laptop, Windows 10 Home	\N
2	HP Envy x360	15.6" laptop, Windows 10 Home	\N
3	Apple MacBook Air	13.3" laptop, macOS High Sierra	\N
4	Lenovo ThinkPad T490	14" laptop, Windows 10 Pro	\N
5	HP Envy\tx460	Personality computer	/home/liora/picturesComputer/HP_Envy_x460.jpeg
6	MSI Cyberpunk Edition	Personality Computer	/home/liora/picturesComputer/MSI_Cyberpunk_Edition.jpeg
\.


--
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.users (id, name, surname, patronymic, age, telephone, login, password, access_level_id) FROM stdin;
9	Роман	Демин	Александрович	30	79278625159	admin	admin	2
8	Михаил	Литвинков	Степанович	24	79278299159	Liorkin	q	1
\.


--
-- Name: access_level_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.access_level_id_seq', 8, true);


--
-- Name: component_options_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.component_options_id_seq', 18, true);


--
-- Name: components_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.components_id_seq', 5, true);


--
-- Name: computer_component_options_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.computer_component_options_id_seq', 22, true);


--
-- Name: computers_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.computers_id_seq', 6, true);


--
-- Name: users_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.users_id_seq', 9, true);


--
-- Name: access_level access_level_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.access_level
    ADD CONSTRAINT access_level_pkey PRIMARY KEY (id);


--
-- Name: component_options component_options_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.component_options
    ADD CONSTRAINT component_options_pkey PRIMARY KEY (id);


--
-- Name: components components_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.components
    ADD CONSTRAINT components_pkey PRIMARY KEY (id);


--
-- Name: computer_component_options computer_component_options_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.computer_component_options
    ADD CONSTRAINT computer_component_options_pkey PRIMARY KEY (id);


--
-- Name: computers computers_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.computers
    ADD CONSTRAINT computers_pkey PRIMARY KEY (id);


--
-- Name: users users_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey PRIMARY KEY (id);


--
-- Name: component_options component_options_component_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.component_options
    ADD CONSTRAINT component_options_component_id_fkey FOREIGN KEY (component_id) REFERENCES public.components(id);


--
-- Name: computer_component_options computer_component_options_component_option_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.computer_component_options
    ADD CONSTRAINT computer_component_options_component_option_id_fkey FOREIGN KEY (component_option_id) REFERENCES public.component_options(id);


--
-- Name: computer_component_options computer_component_options_computer_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.computer_component_options
    ADD CONSTRAINT computer_component_options_computer_id_fkey FOREIGN KEY (computer_id) REFERENCES public.computers(id);


--
-- Name: users users_access_level_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_access_level_id_fkey FOREIGN KEY (access_level_id) REFERENCES public.access_level(id);


--
-- PostgreSQL database dump complete
--

