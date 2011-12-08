use l10nsq_test;

drop table l10n_suggestions_files;
drop table l10n_suggestions_projects;
drop table l10n_suggestions_locations;
drop table l10n_suggestions_strings;
drop table l10n_suggestions_translations;
drop table l10n_suggestions_votes;
drop table l10n_suggestions_users;

create table l10n_suggestions_files like l10nsq.l10n_suggestions_files;
create table l10n_suggestions_projects like l10nsq.l10n_suggestions_projects;
create table l10n_suggestions_locations like l10nsq.l10n_suggestions_locations;
create table l10n_suggestions_strings like l10nsq.l10n_suggestions_strings;
create table l10n_suggestions_translations like l10nsq.l10n_suggestions_translations;
create table l10n_suggestions_votes like l10nsq.l10n_suggestions_votes;
create table l10n_suggestions_users like l10nsq.l10n_suggestions_users;
