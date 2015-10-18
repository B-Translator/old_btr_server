
-- assign the first voter as author of a translation
update btr_translations t
inner join (
    select v.tguid, v.umail, min(v.time) as min_time
    from l10n_feedback_votes v
    group by v.tguid
    ) as v1
on (t.tguid = v1.tguid)
set t.umail = v1.umail, t.time = v1.min_time
where t.umail = ''

