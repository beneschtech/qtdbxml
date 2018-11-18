--
-- PostgreSQL database dump
--

-- Dumped from database version 9.5.14
-- Dumped by pg_dump version 9.6.10

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: xmlconfig_bigdata; Type: TABLE; Schema: public; Owner: leads8
--

CREATE TABLE public.xmlconfig_bigdata (
    xmldata_id integer DEFAULT '-1'::integer NOT NULL,
    data bytea
);


ALTER TABLE public.xmlconfig_bigdata OWNER TO leads8;

--
-- Name: TABLE xmlconfig_bigdata; Type: COMMENT; Schema: public; Owner: leads8
--

COMMENT ON TABLE public.xmlconfig_bigdata IS 'Table with larger data definitions';


--
-- Name: xmlconfig_changehist; Type: TABLE; Schema: public; Owner: leads8
--

CREATE TABLE public.xmlconfig_changehist (
    id integer NOT NULL,
    userid character varying(64) NOT NULL,
    configname character varying(64) NOT NULL,
    changetime timestamp with time zone DEFAULT now() NOT NULL,
    changetext text
);


ALTER TABLE public.xmlconfig_changehist OWNER TO leads8;

--
-- Name: TABLE xmlconfig_changehist; Type: COMMENT; Schema: public; Owner: leads8
--

COMMENT ON TABLE public.xmlconfig_changehist IS 'A history of changes to the configurations defined in the database';


--
-- Name: xmlconfig_changehist_id_seq; Type: SEQUENCE; Schema: public; Owner: leads8
--

CREATE SEQUENCE public.xmlconfig_changehist_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.xmlconfig_changehist_id_seq OWNER TO leads8;

--
-- Name: xmlconfig_changehist_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: leads8
--

ALTER SEQUENCE public.xmlconfig_changehist_id_seq OWNED BY public.xmlconfig_changehist.id;


--
-- Name: xmlconfig_data; Type: TABLE; Schema: public; Owner: leads8
--

CREATE TABLE public.xmlconfig_data (
    id integer NOT NULL,
    type integer NOT NULL,
    parent integer DEFAULT 0 NOT NULL,
    next integer DEFAULT '-1'::integer NOT NULL,
    name character varying(64) NOT NULL,
    data character varying(64),
    revision integer NOT NULL,
    lastrev_id integer DEFAULT '-1'::integer NOT NULL
);


ALTER TABLE public.xmlconfig_data OWNER TO leads8;

--
-- Name: TABLE xmlconfig_data; Type: COMMENT; Schema: public; Owner: leads8
--

COMMENT ON TABLE public.xmlconfig_data IS 'The data for the xml objects, covering the vast majority with data under 64 bytes';


--
-- Name: xmlconfig_data_id_seq; Type: SEQUENCE; Schema: public; Owner: leads8
--

CREATE SEQUENCE public.xmlconfig_data_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.xmlconfig_data_id_seq OWNER TO leads8;

--
-- Name: xmlconfig_data_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: leads8
--

ALTER SEQUENCE public.xmlconfig_data_id_seq OWNED BY public.xmlconfig_data.id;


--
-- Name: xmlconfig_changehist id; Type: DEFAULT; Schema: public; Owner: leads8
--

ALTER TABLE ONLY public.xmlconfig_changehist ALTER COLUMN id SET DEFAULT nextval('public.xmlconfig_changehist_id_seq'::regclass);


--
-- Name: xmlconfig_data id; Type: DEFAULT; Schema: public; Owner: leads8
--

ALTER TABLE ONLY public.xmlconfig_data ALTER COLUMN id SET DEFAULT nextval('public.xmlconfig_data_id_seq'::regclass);


--
-- Name: xmlconfig_bigdata xmlconfig_bigdata_pkey; Type: CONSTRAINT; Schema: public; Owner: leads8
--

ALTER TABLE ONLY public.xmlconfig_bigdata
    ADD CONSTRAINT xmlconfig_bigdata_pkey PRIMARY KEY (xmldata_id);


--
-- Name: xmlconfig_changehist xmlconfig_changehist_pkey; Type: CONSTRAINT; Schema: public; Owner: leads8
--

ALTER TABLE ONLY public.xmlconfig_changehist
    ADD CONSTRAINT xmlconfig_changehist_pkey PRIMARY KEY (id);


--
-- Name: xmlconfig_data xmlconfig_data_pkey; Type: CONSTRAINT; Schema: public; Owner: leads8
--

ALTER TABLE ONLY public.xmlconfig_data
    ADD CONSTRAINT xmlconfig_data_pkey PRIMARY KEY (id);


--
-- Name: xmlconfig_dataidx1; Type: INDEX; Schema: public; Owner: leads8
--

CREATE INDEX xmlconfig_dataidx1 ON public.xmlconfig_data USING btree (parent);


--
-- Name: SCHEMA public; Type: ACL; Schema: -; Owner: pgsql
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM pgsql;
GRANT ALL ON SCHEMA public TO pgsql;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

