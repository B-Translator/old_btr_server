/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_phrases` (
  `pid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Internal numeric identifier for a phrase.',
  `phrase` text COLLATE utf8_bin NOT NULL COMMENT 'The (English) phrase to be translated.',
  `hash` varchar(40) CHARACTER SET ascii DEFAULT NULL,
  `uid_entered` int(11) DEFAULT NULL COMMENT 'ID of the user that inserted this string on the DB.',
  `time_entered` datetime DEFAULT NULL COMMENT 'The time that this string was entered on the DB.',
  `pcount` tinyint(4) DEFAULT '1' COMMENT 'How often this phrase is encountered in all the projects. Can be useful for any heuristics that try to find out which phrases need to be translated first.',
  PRIMARY KEY (`pid`),
  UNIQUE KEY `hash` (`hash`),
  KEY `phrase` (`phrase`(100)),
  KEY `uid_entered` (`uid_entered`,`time_entered`),
  FULLTEXT KEY `phrase_text` (`phrase`)
) ENGINE=MyISAM AUTO_INCREMENT=810815 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='Translatable strings and phrases that are extracted from...';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_locations` (
  `lid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Internal numeric identifier of a line.',
  `pid` int(11) NOT NULL COMMENT 'Reference to the id of the phrase contained in this line.',
  `projectid` int(11) DEFAULT NULL COMMENT 'Reference to the id of the project that contains this line.',
  `packageid` int(11) DEFAULT NULL COMMENT 'Reference to the id of the package that contains the project.',
  `projectname` varchar(100) DEFAULT NULL COMMENT 'The name of the project containing this line.',
  `flags` int(11) DEFAULT NULL COMMENT 'Copied from open-trans.eu',
  PRIMARY KEY (`lid`),
  KEY `pid` (`pid`),
  KEY `projectname` (`projectname`(5))
) ENGINE=InnoDB AUTO_INCREMENT=1149986 DEFAULT CHARSET=utf8 COMMENT='Locations (lines) where a phrase (string) is found.';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_translations` (
  `tid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Internal numeric identifier for a translation.',
  `pid` int(11) NOT NULL COMMENT 'Reference to the id of the phrase that is translated.',
  `lng` varchar(5) CHARACTER SET utf8 NOT NULL COMMENT 'Language code (en, fr, sq_AL, etc.)',
  `translation` varchar(1000) COLLATE utf8_bin NOT NULL COMMENT 'The (suggested) translation of the phrase.',
  `hash` varchar(40) CHARACTER SET ascii DEFAULT NULL,
  `vcount` tinyint(4) DEFAULT '1' COMMENT 'Count of votes received so far. This can be counted on the table Votes, but for convenience is stored here as well.',
  `uid_entered` int(11) DEFAULT NULL COMMENT 'The uid of the user that initially proposed this translation',
  `time_entered` datetime DEFAULT NULL COMMENT 'Time when the translation was entered into the database.',
  PRIMARY KEY (`tid`),
  KEY `pid` (`pid`),
  KEY `uid` (`uid_entered`),
  KEY `time` (`time_entered`),
  KEY `hash` (`hash`),
  FULLTEXT KEY `translation_text` (`translation`)
) ENGINE=MyISAM AUTO_INCREMENT=616387 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='Translations/suggestions of the phrases (strings). For...';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_votes` (
  `vid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Internal numeric identifier for a vote.',
  `tid` int(11) NOT NULL COMMENT 'Reference to the id of the translation which is voted.',
  `uid` int(11) NOT NULL COMMENT 'Reference to the id of the user that submitted the vote.',
  `vtime` datetime DEFAULT NULL COMMENT 'Timestamp of the voting time.',
  PRIMARY KEY (`vid`),
  UNIQUE KEY `tid_uid` (`tid`,`uid`),
  KEY `tid` (`tid`),
  KEY `uid` (`uid`),
  KEY `time` (`vtime`)
) ENGINE=InnoDB AUTO_INCREMENT=425 DEFAULT CHARSET=utf8 COMMENT='Votes for each translation/suggestion.';
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
