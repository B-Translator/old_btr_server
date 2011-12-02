
--use en;
use sq;
--use de;
--use fr;
--use it;
--use es;

/**
 * text comparisons are not efficient and reliable in mysql,
 * so, we use a hash value of the trimmed string in order to
 * make comparisons and to ensure uniqueness of the strings
 */
alter table phrases add column hash varchar(40);
update phrases set hash = sha1(trim(phrase));
--select * from phrases limit 10;

/** check for doublicate phrases */
select *, count(*) from phrases
group by hash having count(*) > 1
order by count(*) desc;

-- run the script cleanup_phrases.sql
-- to fix doublicate phrases
