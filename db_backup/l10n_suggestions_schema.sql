/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_projects` (
  `pid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Auto-increment internal identifier.',
  `project` varchar(100) CHARACTER SET ascii NOT NULL COMMENT 'Project name (with the release appended if needed).',
  `origin` varchar(100) DEFAULT NULL COMMENT 'The origin of the project (where does it come from).',
  `uid` int(11) DEFAULT NULL COMMENT 'Id of the user that registered the project.',
  `time` datetime DEFAULT NULL COMMENT 'The date and time that the project was registered.',
  `active` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'The active or deleted status of the record.',
  PRIMARY KEY (`pid`),
  KEY `project` (`project`)
) ENGINE=InnoDB AUTO_INCREMENT=277 DEFAULT CHARSET=latin1 COMMENT='A project is the software/application which is translated by';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_files` (
  `fid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Auto-increment internal identifier.',
  `file` varchar(200) DEFAULT NULL COMMENT 'The file name (and the path) of the imported file.',
  `pid` int(11) NOT NULL COMMENT 'Reference to the project for which this PO file is a translation.',
  `lng` varchar(10) NOT NULL COMMENT 'The code of the translation language.',
  `headers` text COMMENT 'Headers of the imported PO file, as a long line. Needed mainly for exporting.',
  `uid` int(11) DEFAULT NULL COMMENT 'Id of the user that imported the file.',
  `time` datetime DEFAULT NULL COMMENT 'The date and time that the record was registered.',
  `active` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'The active or deleted status of the record.',
  PRIMARY KEY (`fid`),
  KEY `pid` (`pid`),
  KEY `file` (`file`)
) ENGINE=MyISAM AUTO_INCREMENT=449 DEFAULT CHARSET=latin1 COMMENT='A PO file that is imported and can be exported from the DB.';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_strings` (
  `sid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Internal numeric identifier for a l10n string.',
  `string` text COLLATE utf8_bin NOT NULL COMMENT 'The string to be translated: "$msgid"."\\0"."$msgid_plural"',
  `context` varchar(500) COLLATE utf8_bin DEFAULT NULL COMMENT 'The string context (msgctxt of the PO entry).',
  `hash` char(40) CHARACTER SET ascii DEFAULT NULL COMMENT 'Unique hash of the string: SHA1(CONCAT(string,context)) ',
  `uid` int(11) DEFAULT NULL COMMENT 'ID of the user that inserted this string on the DB.',
  `time` datetime DEFAULT NULL COMMENT 'The time that this string was entered on the DB.',
  `count` tinyint(4) DEFAULT '1' COMMENT 'How often this string is encountered in all the projects. Can be useful for any heuristics that try to find out which strings should be translated first.',
  `active` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'The active/deleted status of the record.',
  PRIMARY KEY (`sid`),
  UNIQUE KEY `hash` (`hash`),
  KEY `string` (`string`(100)),
  KEY `uid` (`uid`,`time`),
  FULLTEXT KEY `string_text` (`string`)
) ENGINE=MyISAM AUTO_INCREMENT=80546 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='Translatable strings that are extracted from...';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_locations` (
  `lid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Internal numeric identifier of a line.',
  `sid` int(11) NOT NULL COMMENT 'Reference to the id of the l10n string contained in this line.',
  `pid` int(11) NOT NULL COMMENT 'Reference to the id of the project that contains this line.',
  `translator_comments` varchar(500) DEFAULT NULL COMMENT 'Translator comments in the PO entry (starting with "# ").',
  `extracted_comments` varchar(500) DEFAULT NULL COMMENT 'Extracted comments in the PO entry (starting with "#. ").',
  `referencies` varchar(500) DEFAULT NULL COMMENT 'Line numbers where the sting occurs (starting with "#: ").',
  `flags` varchar(100) DEFAULT NULL COMMENT 'Flags of the PO entry (starting with "#, ").',
  `previous_msgctxt` varchar(500) DEFAULT NULL COMMENT 'Previous msgctxt in the PO entry (starting with "#| msgctxt ").',
  `previous_msgid` varchar(500) DEFAULT NULL COMMENT 'Previous msgid in the PO entry (starting with "#| msgid ").',
  `previous_msgid_plural` varchar(500) DEFAULT NULL COMMENT 'Previous msgid_plural in the PO entry (starting with "#| msgid_plural ").',
  `active` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'The active/deleted status of the record.',
  PRIMARY KEY (`lid`),
  KEY `sid` (`sid`)
) ENGINE=InnoDB AUTO_INCREMENT=100298 DEFAULT CHARSET=utf8 COMMENT='Locations (lines) where a l10n string is found.';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_translations` (
  `tid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Internal numeric identifier for a translation.',
  `sid` int(11) NOT NULL COMMENT 'Reference to the id of the l10n string that is translated.',
  `lng` varchar(5) CHARACTER SET utf8 NOT NULL COMMENT 'Language code (en, fr, sq_AL, etc.)',
  `translation` varchar(1000) COLLATE utf8_bin NOT NULL COMMENT 'The (suggested) translation of the phrase.',
  `hash` char(40) CHARACTER SET ascii DEFAULT NULL COMMENT 'Unique hash of the translation: SHA1(CONCAT(translation,lng,sid))',
  `count` tinyint(4) DEFAULT '1' COMMENT 'Count of votes received so far. This can be counted on the table Votes, but for convenience is stored here as well.',
  `uid` int(11) DEFAULT NULL COMMENT 'The uid of the user that initially suggested/submitted this translation.',
  `time` datetime DEFAULT NULL COMMENT 'Time when the translation was entered into the database.',
  `active` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'The active/deleted status of the record.',
  PRIMARY KEY (`tid`),
  KEY `uid` (`uid`),
  KEY `time` (`time`),
  KEY `sid` (`sid`),
  KEY `hash` (`hash`),
  FULLTEXT KEY `translation_text` (`translation`)
) ENGINE=MyISAM AUTO_INCREMENT=123880 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='Translations/suggestions of the l10n strings. For...';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_votes` (
  `vid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Internal numeric identifier for a vote.',
  `tid` int(11) NOT NULL COMMENT 'Reference to the id of the translation which is voted.',
  `uid` int(11) NOT NULL COMMENT 'Reference to the id of the user that submitted the vote.',
  `time` datetime DEFAULT NULL COMMENT 'Timestamp of the voting time.',
  `active` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'The active/deleted status of the record.',
  PRIMARY KEY (`vid`),
  UNIQUE KEY `tid_uid` (`tid`,`uid`),
  KEY `tid` (`tid`),
  KEY `uid` (`uid`),
  KEY `time` (`time`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8 COMMENT='Votes for each translation/suggestion.';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_users` (
  `uid` int(11) NOT NULL COMMENT 'The numeric identifier of the user.',
  `points` int(11) DEFAULT '0' COMMENT 'Number of points rewarded for his activity.',
  `config` varchar(250) DEFAULT NULL COMMENT 'Serialized configuration variables.',
  PRIMARY KEY (`uid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Users that contribute translations/suggestions/votes.';
/*!40101 SET character_set_client = @saved_cs_client */;
