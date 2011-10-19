/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_phrases` (
  `pid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Internal numeric identifier for a phrase.',
  `phrase` text COLLATE utf8_bin NOT NULL COMMENT 'The (English) phrase to be translated.',
  `hash` binary(20) DEFAULT NULL,
  `length` tinyint(4) DEFAULT NULL COMMENT 'Length of the phrase (inherited by open-trans.eu).',
  `plural` int(11) DEFAULT NULL COMMENT 'If this is the plural form of another phrase, then this field keeps the id of the singular phrase. Otherwise it is NULL.',
  `pcount` tinyint(4) DEFAULT '1' COMMENT 'How often this phrase is encountered in all the projects. Can be useful for any heuristics that try to find out which phrases need to be translated first.',
  PRIMARY KEY (`pid`),
  UNIQUE KEY `hash` (`hash`),
  KEY `phrase` (`phrase`(100))
) ENGINE=InnoDB AUTO_INCREMENT=851956 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='Translatable strings and phrases that are extracted from...';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_words` (
  `wid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Internal numeric identifier for a word.',
  `word` varchar(100) COLLATE utf8_bin NOT NULL COMMENT 'The word itself.',
  PRIMARY KEY (`wid`),
  UNIQUE KEY `word` (`word`)
) ENGINE=InnoDB AUTO_INCREMENT=65536 DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='Words in all the phrases.';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_wordphrases` (
  `wid` int(11) NOT NULL COMMENT 'Reference to the id of the word.',
  `pid` int(11) NOT NULL COMMENT 'Reference to the id of the phrase.',
  `count` tinyint(4) DEFAULT NULL COMMENT 'The count of the word in the phrase.'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Relations between words and phrases.';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_locations` (
  `lid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Internal numeric identifier of a line.',
  `pid` int(11) NOT NULL COMMENT 'Reference to the id of the phrase contained in this line.',
  `projectid` int(11) NOT NULL COMMENT 'Reference to the id of the project that contains this line.',
  `packageid` int(11) NOT NULL COMMENT 'Reference to the id of the package that contains the project.',
  `projectname` varchar(100) DEFAULT NULL COMMENT 'The name of the project containing this line.',
  `flags` int(11) DEFAULT NULL COMMENT 'Copied from open-trans.eu',
  PRIMARY KEY (`lid`),
  KEY `pid` (`pid`)
) ENGINE=InnoDB AUTO_INCREMENT=1179631 DEFAULT CHARSET=utf8 COMMENT='Locations (lines) where a phrase (string) is found.';
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `l10n_suggestions_translations` (
  `tid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Internal numeric identifier for a translation.',
  `pid` int(11) NOT NULL COMMENT 'Reference to the id of the phrase that is translated.',
  `lng` varchar(5) CHARACTER SET utf8 NOT NULL COMMENT 'Language code (en, fr, sq_AL, etc.)',
  `translation` varchar(1000) COLLATE utf8_bin NOT NULL COMMENT 'The (suggested) translation of the phrase.',
  `vcount` tinyint(4) DEFAULT '1' COMMENT 'Count of votes received so far. This can be counted on the table Votes, but for convenience is stored here as well.',
  `author` int(11) DEFAULT NULL COMMENT 'id of the user that initially proposed this translation',
  PRIMARY KEY (`tid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='Translations/suggestions of the phrases (strings). For...';
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
  KEY `uid` (`uid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Votes for each translation/suggestion.';
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
