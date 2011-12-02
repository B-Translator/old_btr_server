use l10nsq;

/**
 * The connection between the English strings and the
 * corresponding strings in another language (translations)
 * is established through 'locations', since an English
 * string and its translation appear on the same location.
 */

-------------------------------------------------------
-- sq
-------------------------------------------------------

select s.string, len.project, psq.phrase
from l10n_suggestions_strings s
inner join en.phrases pen on (pen.hash = s.hash)
inner join en.locations len on (len.phraseid = pen.id)
inner join sq.locations lsq on (len.locationid = lsq.locationid)
inner join sq.phrases psq on (lsq.phraseid = psq.id)
limit 100;

select count(*)
from l10n_suggestions_strings s
inner join en.phrases pen on (pen.hash = s.hash)
inner join en.locations len on (len.phraseid = pen.id)
inner join sq.locations lsq on (len.locationid = lsq.locationid)
inner join sq.phrases psq on (lsq.phraseid = psq.id);

--select count(*) from l10n_suggestions_strings;

insert into l10n_suggestions_translations (sid, lng, translation)
select s.sid, 'sq', psq.phrase
from l10n_suggestions_strings s
inner join en.phrases pen on (pen.hash = s.hash)
inner join en.locations len on (len.phraseid = pen.id)
inner join sq.locations lsq on (len.locationid = lsq.locationid)
inner join sq.phrases psq on (lsq.phraseid = psq.id);

--select count(*) from l10n_suggestions_translations;
--select * from l10n_suggestions_translations limit 10;

-- The column hash will be used for more efficient and reliable text comparison.
-- hash = sha1(trim(string))
--alter table l10n_suggestions_translations add column hash varchar(40) after translation;
--alter table l10n_suggestions_translations add index hash (hash);

update l10n_suggestions_translations
set hash = sha1(trim(translation))
where hash is null;



/*
-------------------------------------------------------
-- fr
-------------------------------------------------------

select s.string, len.project, pfr.phrase
from l10n_suggestions_strings s
inner join en.phrases pen on (pen.hash = s.hash)
inner join en.locations len on (len.phraseid = pen.id)
inner join fr.locations lfr on (len.locationid = lfr.locationid)
inner join fr.phrases pfr on (lfr.phraseid = pfr.id)
limit 100;

select count(*)
from l10n_suggestions_strings s
inner join en.phrases pen on (pen.hash = s.hash)
inner join en.locations len on (len.phraseid = pen.id)
inner join fr.locations lfr on (len.locationid = lfr.locationid)
inner join fr.phrases pfr on (lfr.phraseid = pfr.id);

--select count(*) from l10n_suggestions_strings;

insert into l10n_suggestions_translations (sid, lng, translation)
select s.sid, 'fr', pfr.phrase
from l10n_suggestions_strings s
inner join en.phrases pen on (pen.hash = s.hash)
inner join en.locations len on (len.phraseid = pen.id)
inner join fr.locations lfr on (len.locationid = lfr.locationid)
inner join fr.phrases pfr on (lfr.phraseid = pfr.id);

--select count(*) from l10n_suggestions_translations where lng='fr';
--select * from l10n_suggestions_translations where lng='fr' limit 10;

-- The column hash will be used for more efficient and reliable text comparison.
-- hash = sha1(trim(string))
--alter table l10n_suggestions_translations add column hash varchar(40) after translation;

update l10n_suggestions_translations
set hash = sha1(trim(translation))
where hash is null;

--alter table l10n_suggestions_translations add index hash (hash);

*/