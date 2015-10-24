DROP TABLE IF EXISTS `btr_diffs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `btr_diffs` (
  `pguid` char(40) CHARACTER SET ascii NOT NULL COMMENT 'Project Globally Unique ID, pguid = SHA1(CONCAT(origin,project))',
  `lng` varchar(5) COLLATE utf8_bin NOT NULL COMMENT 'The language of translation.',
  `nr` smallint(5) unsigned NOT NULL COMMENT 'Incremental number of the diffs of a project-language.',
  `diff` mediumblob COMMENT 'The content of the unified diff (diff -u).',
  `ediff` mediumblob COMMENT 'The embedded diff (generated with the command poediff of pology).',
  `comment` varchar(200) COLLATE utf8_bin DEFAULT NULL COMMENT 'Comment/description of the diff.',
  `uid` int(11) DEFAULT NULL COMMENT 'Id of the user that inserted the diff.',
  `time` datetime NOT NULL COMMENT 'The date and time that the diff was saved.',
  PRIMARY KEY (`pguid`,`lng`,`nr`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='Diffs between the current state and the last snapshot.';
/*!40101 SET character_set_client = @saved_cs_client */;
DROP TABLE IF EXISTS `btr_snapshots`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `btr_snapshots` (
  `pguid` char(40) COLLATE utf8_bin NOT NULL COMMENT 'Reference to the project.',
  `lng` varchar(10) COLLATE utf8_bin NOT NULL COMMENT 'The language of translation.',
  `snapshot` mediumblob NOT NULL COMMENT 'The content of the tgz archive.',
  `uid` int(11) NOT NULL COMMENT 'Id of the user that updated the snapshot for the last time.',
  `time` datetime NOT NULL COMMENT 'The time of last update.',
  PRIMARY KEY (`pguid`,`lng`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='Snapshots are tgz archives of project-lng translation files.';
/*!40101 SET character_set_client = @saved_cs_client */;
DROP TABLE IF EXISTS `btr_files`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `btr_files` (
  `fid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Auto-increment internal identifier.',
  `filename` varchar(250) COLLATE utf8_bin DEFAULT NULL COMMENT 'The path and filename of the imported PO file.',
  `content` mediumblob NOT NULL COMMENT 'The original content of the imported file.',
  `hash` char(40) CHARACTER SET ascii NOT NULL COMMENT 'The SHA1() hash of the whole file content.',
  `potid` int(11) NOT NULL COMMENT 'Reference to the project for which this PO file is a translation.',
  `lng` varchar(10) COLLATE utf8_bin NOT NULL COMMENT 'The code of the translation language.',
  `headers` text COLLATE utf8_bin COMMENT 'Headers of the imported PO file, as a long line. Needed mainly for exporting.',
  `comments` text COLLATE utf8_bin COMMENT 'Translator comments of the file (above the header entry).',
  `uid` int(11) DEFAULT NULL COMMENT 'Id of the user that imported the file.',
  `time` datetime DEFAULT NULL COMMENT 'The date and time that the record was registered.',
  PRIMARY KEY (`fid`),
  KEY `hash` (`hash`),
  KEY `potid` (`potid`)
) ENGINE=InnoDB AUTO_INCREMENT=17933 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='A PO file that is imported and can be exported from the DB.';
/*!40101 SET character_set_client = @saved_cs_client */;
DROP TABLE IF EXISTS `btr_projects`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `btr_projects` (
  `pguid` char(40) CHARACTER SET ascii NOT NULL COMMENT 'Project Globally Unique ID, pguid = SHA1(CONCAT(origin,project))',
  `project` varchar(100) CHARACTER SET utf8 NOT NULL COMMENT 'Project name (with the release appended if needed).',
  `origin` varchar(100) CHARACTER SET utf8 DEFAULT NULL COMMENT 'The origin of the project (where does it come from).',
  `uid` int(11) DEFAULT NULL COMMENT 'Id of the user that registered the project.',
  `time` datetime DEFAULT NULL COMMENT 'The date and time that the project was registered.',
  PRIMARY KEY (`pguid`),
  KEY `project` (`project`),
  KEY `origin` (`origin`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='A project is the software/application which is translated by';
/*!40101 SET character_set_client = @saved_cs_client */;
DROP TABLE IF EXISTS `btr_templates`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `btr_templates` (
  `potid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Auto-increment internal identifier.',
  `tplname` varchar(200) CHARACTER SET ascii COLLATE ascii_bin NOT NULL COMMENT 'The name of the POT template (to distinguish it from the other templates of the same project).',
  `filename` varchar(250) COLLATE utf8_bin DEFAULT NULL COMMENT 'The path and name of the imported POT file.',
  `pguid` char(40) CHARACTER SET ascii NOT NULL COMMENT 'Reference to the project to which this PO template belongs.',
  `uid` int(11) DEFAULT NULL COMMENT 'Id of the user that registered the project.',
  `time` datetime DEFAULT NULL COMMENT 'The date and time that the project was registered.',
  PRIMARY KEY (`potid`),
  KEY `pguid` (`pguid`)
) ENGINE=InnoDB AUTO_INCREMENT=14133 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT=' Templates are the POT files that are imported.';
/*!40101 SET character_set_client = @saved_cs_client */;
DROP TABLE IF EXISTS `btr_locations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `btr_locations` (
  `lid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Internal numeric identifier of a line.',
  `sguid` char(40) CHARACTER SET ascii NOT NULL COMMENT 'Reference to the id of the l10n string contained in this line.',
  `potid` int(11) NOT NULL COMMENT 'Reference to the id of the template (POT) that contains this line.',
  `translator_comments` varchar(1000) COLLATE utf8_bin DEFAULT NULL COMMENT 'Translator comments in the PO entry (starting with "# ").',
  `extracted_comments` varchar(1000) COLLATE utf8_bin DEFAULT NULL COMMENT 'Extracted comments in the PO entry (starting with "#. ").',
  `line_references` varchar(1000) COLLATE utf8_bin DEFAULT NULL COMMENT 'Line numbers where the sting occurs (starting with "#: ").',
  `flags` varchar(1000) COLLATE utf8_bin DEFAULT NULL COMMENT 'Flags of the PO entry (starting with "#, ").',
  `previous_msgctxt` varchar(1000) COLLATE utf8_bin DEFAULT NULL COMMENT 'Previous msgctxt in the PO entry (starting with "#| msgctxt ").',
  `previous_msgid` varchar(1000) COLLATE utf8_bin DEFAULT NULL COMMENT 'Previous msgid in the PO entry (starting with "#| msgid ").',
  `previous_msgid_plural` varchar(1000) COLLATE utf8_bin DEFAULT NULL COMMENT 'Previous msgid_plural in the PO entry (starting with "#| msgid_plural ").',
  PRIMARY KEY (`lid`),
  KEY `sguid` (`sguid`),
  KEY `potid` (`potid`)
) ENGINE=InnoDB AUTO_INCREMENT=2254204 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='Locations (lines) where a l10n string is found.';
/*!40101 SET character_set_client = @saved_cs_client */;
DROP TABLE IF EXISTS `btr_strings`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `btr_strings` (
  `string` varchar(1000) COLLATE utf8_bin NOT NULL COMMENT 'The string to be translated: "$msgid"."\\0"."$msgid_plural"',
  `context` varchar(1000) COLLATE utf8_bin DEFAULT NULL COMMENT 'The string context (msgctxt of the PO entry).',
  `sguid` char(40) CHARACTER SET ascii NOT NULL DEFAULT '' COMMENT 'Globally Unique ID of the string, generated as a hash of the string and context: SHA1(CONCAT(string,context)) ',
  `uid` int(11) DEFAULT NULL COMMENT 'ID of the user that inserted this string on the DB.',
  `time` datetime DEFAULT NULL COMMENT 'The time that this string was entered on the DB.',
  `count` smallint(6) DEFAULT '1' COMMENT 'How often this string is encountered in all the projects. Can be useful for any heuristics that try to find out which strings should be translated first.',
  `active` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'The active/deleted status of the record.',
  PRIMARY KEY (`sguid`),
  KEY `string` (`string`(100)),
  KEY `uid` (`uid`,`time`),
  FULLTEXT KEY `string_text` (`string`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='Translatable strings that are extracted from...';
/*!40101 SET character_set_client = @saved_cs_client */;
DROP TABLE IF EXISTS `btr_translations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `btr_translations` (
  `sguid` char(40) CHARACTER SET ascii NOT NULL COMMENT 'Reference to the id of the l10n string that is translated.',
  `lng` varchar(5) COLLATE utf8_bin NOT NULL COMMENT 'Language code (en, fr, sq_AL, etc.)',
  `translation` varchar(1000) COLLATE utf8_bin NOT NULL COMMENT 'The (suggested) translation of the phrase.',
  `tguid` char(40) CHARACTER SET ascii NOT NULL COMMENT 'Globally Unique ID of the translation, defined as hash: SHA1(CONCAT(translation,lng,sguid))',
  `count` smallint(6) DEFAULT '1' COMMENT 'Count of votes received so far. This can be counted on the table Votes, but for convenience is stored here as well.',
  `umail` varchar(250) CHARACTER SET utf8 NOT NULL COMMENT 'The email of the user that submitted this suggestion.',
  `ulng` varchar(5) CHARACTER SET utf8 NOT NULL COMMENT 'The translation language of the user that submitted this suggestion.',
  `time` datetime DEFAULT NULL COMMENT 'Time when the translation was entered into the database.',
  `active` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'The active/deleted status of the record.',
  PRIMARY KEY (`tguid`),
  KEY `time` (`time`),
  KEY `sguid` (`sguid`),
  KEY `umail` (`umail`(20)),
  FULLTEXT KEY `translation_text` (`translation`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='Translations/suggestions of the l10n strings. For...';
/*!40101 SET character_set_client = @saved_cs_client */;
DROP TABLE IF EXISTS `btr_translations_trash`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `btr_translations_trash` (
  `sguid` char(40) CHARACTER SET ascii NOT NULL COMMENT 'Reference to the id of the l10n string that is translated.',
  `lng` varchar(5) COLLATE utf8_bin NOT NULL COMMENT 'Language code (en, fr, sq_AL, etc.)',
  `translation` varchar(1000) COLLATE utf8_bin NOT NULL COMMENT 'The (suggested) translation of the phrase.',
  `tguid` char(40) CHARACTER SET ascii NOT NULL COMMENT 'Globally Unique ID of the translation, defined as hash: SHA1(CONCAT(translation,lng,sguid))',
  `count` smallint(6) DEFAULT '1' COMMENT 'Count of votes received so far. This can be counted on the table Votes, but for convenience is stored here as well.',
  `umail` varchar(250) CHARACTER SET utf8 NOT NULL COMMENT 'The email of the user that submitted this suggestion.',
  `ulng` varchar(5) CHARACTER SET utf8 NOT NULL COMMENT 'The translation language of the user that submitted this suggestion.',
  `time` datetime DEFAULT NULL COMMENT 'Time when the translation was entered into the database.',
  `active` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'The active/deleted status of the record.',
  `d_umail` varchar(250) CHARACTER SET utf8 NOT NULL COMMENT 'The email of the user that deleted this translation.',
  `d_ulng` varchar(5) CHARACTER SET utf8 NOT NULL COMMENT 'The language of the user that deleted this translation.',
  `d_time` datetime NOT NULL COMMENT 'Timestamp of the deletion time.',
  KEY `time` (`time`),
  KEY `sguid` (`sguid`),
  KEY `umail` (`umail`(10)),
  KEY `d_time` (`d_time`),
  KEY `d_umail` (`d_umail`(10)),
  KEY `tguid` (`tguid`),
  FULLTEXT KEY `translation_text` (`translation`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='Translations that are deleted are saved on the trash table.';
/*!40101 SET character_set_client = @saved_cs_client */;
DROP TABLE IF EXISTS `btr_votes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `btr_votes` (
  `vid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Internal numeric identifier for a vote.',
  `tguid` char(40) CHARACTER SET ascii NOT NULL COMMENT 'Reference to the id of the translation which is voted.',
  `umail` varchar(250) NOT NULL COMMENT 'Email of the user that submitted the vote.',
  `ulng` varchar(5) NOT NULL COMMENT 'Translation language of the user that submitted the vote.',
  `time` datetime DEFAULT NULL COMMENT 'Timestamp of the voting time.',
  `active` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'The active/deleted status of the record.',
  PRIMARY KEY (`vid`),
  UNIQUE KEY `umail_ulng_tguid` (`umail`(20),`ulng`,`tguid`),
  KEY `time` (`time`),
  KEY `tguid` (`tguid`),
  KEY `umail` (`umail`(20))
) ENGINE=InnoDB AUTO_INCREMENT=70 DEFAULT CHARSET=utf8 COMMENT='Votes for each translation/suggestion.';
/*!40101 SET character_set_client = @saved_cs_client */;
DROP TABLE IF EXISTS `btr_votes_trash`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `btr_votes_trash` (
  `vid` int(11) NOT NULL COMMENT 'Internal numeric identifier for a vote.',
  `tguid` char(40) CHARACTER SET ascii NOT NULL COMMENT 'Reference to the id of the translation which is voted.',
  `umail` varchar(250) NOT NULL COMMENT 'Email of the user that submitted the vote.',
  `ulng` varchar(5) NOT NULL COMMENT 'Translation language of the user that submitted the vote.',
  `time` datetime DEFAULT NULL COMMENT 'Timestamp of the voting time.',
  `active` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'The active/deleted status of the record.',
  `d_time` datetime NOT NULL COMMENT 'Timestamp of the deletion time.',
  KEY `time` (`time`),
  KEY `tguid` (`tguid`),
  KEY `d_time` (`d_time`),
  KEY `umail_ulng_tguid` (`umail`(20),`ulng`,`tguid`),
  KEY `vid` (`vid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Votes that are deleted are saved on the trash table.';
/*!40101 SET character_set_client = @saved_cs_client */;
DROP TABLE IF EXISTS `btr_users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `btr_users` (
  `umail` varchar(250) NOT NULL COMMENT 'Email of the user.',
  `ulng` varchar(5) NOT NULL COMMENT 'Translation language of the user.',
  `uid` int(11) NOT NULL COMMENT 'The numeric identifier of the user.',
  `name` varchar(60) NOT NULL COMMENT 'Username',
  `status` tinyint(4) NOT NULL DEFAULT '0' COMMENT 'Disabled (0) or active (1).',
  `points` int(11) DEFAULT '0' COMMENT 'Number of points rewarded for his activity.',
  `config` varchar(250) DEFAULT NULL COMMENT 'Serialized configuration variables.',
  PRIMARY KEY (`umail`,`ulng`,`uid`),
  KEY `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Users that contribute translations/suggestions/votes.';
/*!40101 SET character_set_client = @saved_cs_client */;
DROP TABLE IF EXISTS `btr_user_project_roles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `btr_user_project_roles` (
  `umail` varchar(250) NOT NULL COMMENT 'Email of the user.',
  `ulng` varchar(5) NOT NULL COMMENT 'Translation language of the user.',
  `pguid` char(40) CHARACTER SET ascii NOT NULL COMMENT 'Project ID.',
  `role` varchar(20) CHARACTER SET ascii NOT NULL,
  PRIMARY KEY (`umail`,`ulng`,`pguid`,`role`),
  KEY `user` (`umail`,`ulng`),
  KEY `project` (`pguid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Roles of a user in a project.';
/*!40101 SET character_set_client = @saved_cs_client */;
DROP TABLE IF EXISTS `btr_mv_sample`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `btr_mv_sample` (
  `string` varchar(1000) COLLATE utf8_general_ci NOT NULL,
  KEY `string` (`string`(100))
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='Materialized view for strings of a vocabulary (used to speed-up autocompletion).';
/*!40101 SET character_set_client = @saved_cs_client */;
