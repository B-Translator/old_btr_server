<?php
/**
 * @file
 * btranslator_content.features.node_export_features.inc
 */

/**
 * Implements hook_node_export_features_default().
 */
function btranslator_content_node_export_features_default() {
  $node_export = array(
  'code_string' => 'array(
  (object) array(
      \'vid\' => \'10\',
      \'uid\' => \'1\',
      \'title\' => \'About\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'e5ac3a68-b17f-feb4-95e6-21b5907f7816\',
      \'nid\' => \'10\',
      \'type\' => \'page\',
      \'language\' => \'en\',
      \'created\' => \'1342860939\',
      \'changed\' => \'1343044169\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'0edea5b7-aaf1-2214-8d60-d73c9faee694\',
      \'revision_timestamp\' => \'1343044169\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "Kjo faqe ka si qëllim të ndihmojë dhe të koordinojë përkthimin e programeve kompjuterike në gjuhën shqipe. (...së shpejti)\\r\\n\\r\\n<iframe src=\\"http://www.facebook.com/plugins/likebox.php?href=http%3A%2F%2Fwww.facebook.com%2FE.Duam.Kompjuterin.Shqip&amp;width=600&amp;colorscheme=light&amp;show_faces=true&amp;border_color&amp;stream=true&amp;header=false&amp;height=550\\" scrolling=\\"no\\" frameborder=\\"0\\" style=\\"border:none; overflow:hidden; width:600px; height:550px;\\" allowTransparency=\\"true\\"></iframe>",
            \'summary\' => "Kjo faqe ka si qëllim të ndihmojë dhe të koordinojë përkthimin e programeve kompjuterike në gjuhën shqipe. (...së shpejti)\\r\\n\\r\\n<iframe src=\\"http://www.facebook.com/plugins/likebox.php?href=http%3A%2F%2Fwww.facebook.com%2FE.Duam.Kompjuterin.Shqip&amp;width=600&amp;colorscheme=light&amp;show_faces=true&amp;border_color&amp;stream=true&amp;header=false&amp;height=550\\" scrolling=\\"no\\" frameborder=\\"0\\" style=\\"border:none; overflow:hidden; width:600px; height:550px;\\" allowTransparency=\\"true\\"></iframe>",
            \'format\' => \'full_html\',
            \'safe_value\' => "<p>Kjo faqe ka si qëllim të ndihmojë dhe të koordinojë përkthimin e programeve kompjuterike në gjuhën shqipe. (...së shpejti)</p>\\n<iframe src=\\"http://www.facebook.com/plugins/likebox.php?href=http%3A%2F%2Fwww.facebook.com%2FE.Duam.Kompjuterin.Shqip&amp;width=600&amp;colorscheme=light&amp;show_faces=true&amp;border_color&amp;stream=true&amp;header=false&amp;height=550\\" scrolling=\\"no\\" frameborder=\\"0\\" style=\\"border:none; overflow:hidden; width:600px; height:550px;\\" allowTransparency=\\"true\\"></iframe>",
            \'safe_summary\' => "<p>Kjo faqe ka si qëllim të ndihmojë dhe të koordinojë përkthimin e programeve kompjuterike në gjuhën shqipe. (...së shpejti)</p>\\n<iframe src=\\"http://www.facebook.com/plugins/likebox.php?href=http%3A%2F%2Fwww.facebook.com%2FE.Duam.Kompjuterin.Shqip&amp;width=600&amp;colorscheme=light&amp;show_faces=true&amp;border_color&amp;stream=true&amp;header=false&amp;height=550\\" scrolling=\\"no\\" frameborder=\\"0\\" style=\\"border:none; overflow:hidden; width:600px; height:550px;\\" allowTransparency=\\"true\\"></iframe>",
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1342860939\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/about\',
        \'title\' => \'About\',
        \'identifier\' => \'node/10\',
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => array(
        \'pid\' => \'9\',
        \'source\' => \'node/10\',
        \'alias\' => \'about\',
        \'language\' => \'en\',
      ),
      \'menu\' => array(
        \'link_title\' => \'About\',
        \'mlid\' => 0,
        \'plid\' => \'0\',
        \'menu_name\' => \'main-menu\',
        \'weight\' => \'-45\',
        \'options\' => array(),
        \'module\' => \'menu\',
        \'expanded\' => \'0\',
        \'hidden\' => \'0\',
        \'has_children\' => \'0\',
        \'customized\' => 0,
        \'parent_depth_limit\' => 8,
        \'description\' => \'About this website.\',
        \'enabled\' => 1,
      ),
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'2\',
      \'uid\' => \'1\',
      \'title\' => \'Terms of Service\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'60df27dc-1b3a-8eb4-5512-ff65210dbf9b\',
      \'nid\' => \'2\',
      \'type\' => \'page\',
      \'language\' => \'en\',
      \'created\' => \'1342858068\',
      \'changed\' => \'1342858068\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'12f07370-d145-7c74-6122-27a80d51ac49\',
      \'revision_timestamp\' => \'1342858068\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'The services of this application will be used in good faith. Any disputes will be solved with agreement and mutual understanding.\',
            \'summary\' => \'\',
            \'format\' => \'filtered_html\',
            \'safe_value\' => "<p>The services of this application will be used in good faith. Any disputes will be solved with agreement and mutual understanding.</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1342858068\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/terms\',
        \'title\' => \'Terms of Service\',
        \'identifier\' => \'node/2\',
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => array(
        \'pid\' => \'2\',
        \'source\' => \'node/2\',
        \'alias\' => \'terms\',
        \'language\' => \'en\',
      ),
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'15\',
      \'uid\' => \'1\',
      \'title\' => \'RSS Feeds\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'1\',
      \'sticky\' => \'1\',
      \'vuuid\' => \'01cdfd42-3b26-b374-5546-8471e65d80c8\',
      \'nid\' => \'15\',
      \'type\' => \'simplenews\',
      \'language\' => \'en\',
      \'created\' => \'1352581918\',
      \'changed\' => \'1358642312\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'23dd33db-a9ef-2394-41cd-c3dd3906a9b2\',
      \'revision_timestamp\' => \'1358642312\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<p><span style="font-family: arial, helvetica, sans-serif;">Së fundmi janë implementuar edhe RSS feeds, të cilat të lejojnë të ndjekësh me lehtësi përkthimet/sugjerimet më të fundit.&nbsp;Adresa URL e tyre është:&nbsp;http://l10n.org.al/translations/rss-feed</span></p><p><span style="font-family: arial, helvetica, sans-serif;">Kjo adresë mund të përdoret në çdo <em>news/feed reader</em>, i cili lidhet periodikisht me këtë adresë dhe merr të rejat e fundit prej saj.&nbsp;Shpeshtësia e përtëritjes është mirë të jetë një herë në 1 ose 2 orë, meqënëse edhe të rejat e faqes rikrijohen të shumtën 1 herë në 2 orë, dhe përmbajnë vetëm përkthimet e fundit që nga dita e kaluar.</span></p><p><span style="font-family: arial, helvetica, sans-serif;">E njëjta adresë mund të përdoret edhe te <em>feed aggregator</em> në faqet tuaja, për të shfaqur të rejat më të fundit nga faqja e përkthimeve. Si shembull mund të shihni <em>feed aggregator</em> te vetë faqja e përkthimeve, i cili tregon përkthimet më të fundit:&nbsp;http://l10n.org.al/aggregator/sources/1</span></p><p><span style="font-family: arial, helvetica, sans-serif;">Në fakt, përkthimet mund të filtrohen edhe në bazë të projekteve, p.sh: &nbsp;https://l10n.org.al/translations/rss-feed/LibreOffice, ose &nbsp;https://l10n.org.al/translations/rss-feed/LibreOffice/sw. Por për momentin kjo nuk është shumë e dobishme, meqënëse edhe fluksi i përkthimeve nuk është shumë i lartë.</span></p><p><span style="font-family: arial, helvetica, sans-serif;">Ju lutem më vini në dijeni nëse shihni ndonjë gjë që mund të rregullohet ose të përmirësohet.</span></p>\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Së fundmi janë implementuar edhe RSS feeds, të cilat të lejojnë të ndjekësh me lehtësi përkthimet/sugjerimet më të fundit.&nbsp;Adresa URL e tyre është:&nbsp;<a href=\\"http://l10n.org.al/translations/rss-feed\\">http://l10n.org.al/translations/rss-feed</a></span></p>\\n<p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Kjo adresë mund të përdoret në çdo <em>news/feed reader</em>, i cili lidhet periodikisht me këtë adresë dhe merr të rejat e fundit prej saj.&nbsp;Shpeshtësia e përtëritjes është mirë të jetë një herë në 1 ose 2 orë, meqënëse edhe të rejat e faqes rikrijohen të shumtën 1 herë në 2 orë, dhe përmbajnë vetëm përkthimet e fundit që nga dita e kaluar.</span></p>\\n<p><span style=\\"font-family: arial, helvetica, sans-serif;\\">E njëjta adresë mund të përdoret edhe te <em>feed aggregator</em> në faqet tuaja, për të shfaqur të rejat më të fundit nga faqja e përkthimeve. Si shembull mund të shihni <em>feed aggregator</em> te vetë faqja e përkthimeve, i cili tregon përkthimet më të fundit:&nbsp;<a href=\\"http://l10n.org.al/aggregator/sources/1\\">http://l10n.org.al/aggregator/sources/1</a></span></p>\\n<p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Në fakt, përkthimet mund të filtrohen edhe në bazë të projekteve, p.sh: &nbsp;<a href=\\"https://l10n.org.al/translations/rss-feed/LibreOffice\\">https://l10n.org.al/translations/rss-feed/LibreOffice</a>, ose &nbsp;<a href=\\"https://l10n.org.al/translations/rss-feed/LibreOffice/sw\\">https://l10n.org.al/translations/rss-feed/LibreOffice/sw</a>. Por për momentin kjo nuk është shumë e dobishme, meqënëse edhe fluksi i përkthimeve nuk është shumë i lartë.</span></p>\\n<p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Ju lutem më vini në dijeni nëse shihni ndonjë gjë që mund të rregullohet ose të përmirësohet.</span></p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_simplenews_term\' => array(
        \'en\' => array(
          array(
            \'tid\' => \'3\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1352581918\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/node/15\',
        \'title\' => \'RSS Feeds\',
        \'identifier\' => \'node/15\',
      ),
      \'simplenews\' => (object) array(
          \'nid\' => \'15\',
          \'tid\' => \'3\',
          \'status\' => \'2\',
          \'sent_subscriber_count\' => \'25\',
          \'name\' => \'Njoftime\',
          \'description\' => \'Njoftime të brendëshme për personat e rregjistruar te Përkthimi i Programeve në Shqip.\',
          \'weight\' => \'0\',
        ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'8\',
      \'uid\' => \'1\',
      \'title\' => \'Vendosja e Gjuhës Shqipe në Ubuntu\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'2\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'2cccc4aa-18bf-0ca4-0195-d060316ad28a\',
      \'nid\' => \'8\',
      \'type\' => \'book\',
      \'language\' => \'en\',
      \'created\' => \'1342860537\',
      \'changed\' => \'1350381309\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'31a070fa-03e8-4af4-5d42-5bfacde0a099\',
      \'revision_timestamp\' => \'1350381309\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<div style="color: #4d4d4d; font-family: Times, serif; font-size: 16px;">&nbsp;</div><div style="color: #4d4d4d; font-family: Times, serif; font-size: 16px;">Gjuha shqipe në Ubuntu mund të vendoset shumë kollaj, nëse keni lidhje me internetin.</div><div style="color: #4d4d4d; font-family: Times, serif; font-size: 16px;">&nbsp;</div><div class="separator" style="color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;">&nbsp;</div><ul style="padding-right: 2.5em; padding-left: 2.5em; margin-top: 0.5em; margin-bottom: 0.5em; margin-left: 0px; line-height: 1.4; list-style-image: initial;"><li style="margin-bottom: 0.25em; border-style: none;">Fillimisht hap&nbsp;<strong>System Settings</strong>, dhe aty zgjidh&nbsp;<strong>Language Support</strong>&nbsp;(siç tregohet në figurat e mëposhtme):</li></ul><p>&nbsp;</p><div class="separator" style="color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;"><a style="color: #a30200; margin-left: 1em; margin-right: 1em;" href="http://4.bp.blogspot.com/-an2BzWNGKO8/UH0oqJd66WI/AAAAAAAAAyY/1dKtmIySSRY/s1600/system_settings.png"><img style="border-style: none; position: relative;" src="http://4.bp.blogspot.com/-an2BzWNGKO8/UH0oqJd66WI/AAAAAAAAAyY/1dKtmIySSRY/s1600/system_settings.png" alt="" border="0"></a></div><p>&nbsp;</p><div class="separator" style="color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;"><a style="color: #a30200; margin-left: 1em; margin-right: 1em;" href="http://3.bp.blogspot.com/-1dfq2PSFgwU/UH0orBzZKsI/AAAAAAAAAyk/xjEIma6Ah2w/s1600/system_settings_window.png"><img style="border-style: none; position: relative;" src="http://3.bp.blogspot.com/-1dfq2PSFgwU/UH0orBzZKsI/AAAAAAAAAyk/xjEIma6Ah2w/s1600/system_settings_window.png" alt="" width="640" height="567" border="0"></a></div><p><span style="color: #4d4d4d; font-size: 15px; font-family: Times, serif;">&nbsp;</span></p><ul style="padding-right: 2.5em; padding-left: 2.5em; margin-top: 0.5em; margin-bottom: 0.5em; margin-left: 0px; list-style-image: initial; color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px;"><li style="margin-bottom: 0.25em; border-style: none;"><span style="font-family: Times, serif;"><span style="font-size: 16px;">Pastaj kliko butonin</span><span style="font-size: 16px;">&nbsp;</span><strong style="font-size: 16px;">Install/Remove Languages…</strong><span style="font-size: 16px;">, zgjidh nga lista gjuhën shqipe (Albanian), dhe kliko</span><span style="font-size: 16px;">&nbsp;</span><strong style="font-size: 16px;">Apply Changes</strong><span style="font-size: 16px;">:</span></span></li></ul><p>&nbsp;</p><div class="separator" style="color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;"><a style="color: #a30200; margin-left: 1em; margin-right: 1em;" href="http://1.bp.blogspot.com/-7ax8o5cpR2A/UH0ol0cwJ-I/AAAAAAAAAx8/Mj7m4cV_wjA/s1600/install_remove_languages.png"><img style="border-style: none; position: relative;" src="http://1.bp.blogspot.com/-7ax8o5cpR2A/UH0ol0cwJ-I/AAAAAAAAAx8/Mj7m4cV_wjA/s1600/install_remove_languages.png" alt="" width="640" height="552" border="0"></a></div><p><span style="color: #4d4d4d; font-family: Times, serif; font-size: 16px;"><br></span><span style="color: #4d4d4d; font-size: 15px; font-family: Times, serif;"><br></span></p><ul style="padding-right: 2.5em; padding-left: 2.5em; margin-top: 0.5em; margin-bottom: 0.5em; margin-left: 0px; list-style-image: initial; color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px;"><li style="margin-bottom: 0.25em; border-style: none;"><span style="font-family: Times, serif;"><span style="font-size: 16px;">Prit deri sa të shkarkohen dhe të aplikohen të gjitha ndryshimet:</span></span></li></ul><p><br style="color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px;"><span style="color: #4d4d4d; font-size: 15px; font-family: Times, serif;"><br></span></p><div class="separator" style="color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;"><a style="color: #a30200; margin-left: 1em; margin-right: 1em;" href="http://2.bp.blogspot.com/-eGlksK5n7ms/UH0oigGWoRI/AAAAAAAAAxs/FxmVBmlS6sU/s1600/applying_changes.png"><img style="border-style: none; position: relative;" src="http://2.bp.blogspot.com/-eGlksK5n7ms/UH0oigGWoRI/AAAAAAAAAxs/FxmVBmlS6sU/s1600/applying_changes.png" alt="" width="640" height="484" border="0"></a></div><p><span style="color: #4d4d4d; font-size: 15px; font-family: Times, serif;"><br></span><span style="color: #4d4d4d; font-size: 15px; font-family: Times, serif;"><br></span></p><ul style="padding-right: 2.5em; padding-left: 2.5em; margin-top: 0.5em; margin-bottom: 0.5em; margin-left: 0px; list-style-image: initial; color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px;"><li style="margin-bottom: 0.25em; border-style: none;"><span style="font-family: Times, serif;"><span style="font-size: 16px;">Tek lista e gjuhëve, gjeje gjuhën</span><span style="font-size: 16px;">&nbsp;</span><em style="font-size: 16px;">Albanian</em><span style="font-size: 16px;">&nbsp;</span><span style="font-size: 16px;">(duhet të jetë me ngjyrë gri), tëhiqe me shigjetën e miushit dhe vendose të parën në listë.&nbsp;</span><span style="font-size: 16px;">Kliko gjithashtu edhe butonin</span><span style="font-size: 16px;">&nbsp;</span><strong style="font-size: 16px;">Apply System-Wide</strong><span style="font-size: 16px;">. Ndryshimi i gjuhës do të hyj në fuqi pasi të dilni dhe të hyni përsëri në ambjentin e punës.</span></span></li></ul><p><br style="color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px;"><span style="color: #4d4d4d; font-family: Times, serif; font-size: 16px;"><br></span></p><div class="separator" style="color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;"><a style="color: #a30200; margin-left: 1em; margin-right: 1em;" href="http://3.bp.blogspot.com/-Spq1itMm3iU/UH0onZ4wVPI/AAAAAAAAAyA/wG5j43vDS0s/s1600/language_support_1.png"><img style="border-style: none; position: relative;" src="http://3.bp.blogspot.com/-Spq1itMm3iU/UH0onZ4wVPI/AAAAAAAAAyA/wG5j43vDS0s/s1600/language_support_1.png" alt="" width="640" height="555" border="0"></a></div><div>&nbsp;</div>\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<div style=\\"color: #4d4d4d; font-family: Times, serif; font-size: 16px;\\">&nbsp;</div>\\n<div style=\\"color: #4d4d4d; font-family: Times, serif; font-size: 16px;\\">Gjuha shqipe në Ubuntu mund të vendoset shumë kollaj, nëse keni lidhje me internetin.</div>\\n<div style=\\"color: #4d4d4d; font-family: Times, serif; font-size: 16px;\\">&nbsp;</div>\\n<div class=\\"separator\\" style=\\"color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;\\">&nbsp;</div>\\n<ul style=\\"padding-right: 2.5em; padding-left: 2.5em; margin-top: 0.5em; margin-bottom: 0.5em; margin-left: 0px; line-height: 1.4; list-style-image: initial;\\">\\n<li style=\\"margin-bottom: 0.25em; border-style: none;\\">Fillimisht hap&nbsp;<strong>System Settings</strong>, dhe aty zgjidh&nbsp;<strong>Language Support</strong>&nbsp;(siç tregohet në figurat e mëposhtme):</li>\\n</ul>\\n<p>&nbsp;</p>\\n<div class=\\"separator\\" style=\\"color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;\\"><a style=\\"color: #a30200; margin-left: 1em; margin-right: 1em;\\" href=\\"http://4.bp.blogspot.com/-an2BzWNGKO8/UH0oqJd66WI/AAAAAAAAAyY/1dKtmIySSRY/s1600/system_settings.png\\"><img style=\\"border-style: none; position: relative;\\" src=\\"http://4.bp.blogspot.com/-an2BzWNGKO8/UH0oqJd66WI/AAAAAAAAAyY/1dKtmIySSRY/s1600/system_settings.png\\" alt=\\"\\" border=\\"0\\"></a></div>\\n<p>&nbsp;</p>\\n<div class=\\"separator\\" style=\\"color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;\\"><a style=\\"color: #a30200; margin-left: 1em; margin-right: 1em;\\" href=\\"http://3.bp.blogspot.com/-1dfq2PSFgwU/UH0orBzZKsI/AAAAAAAAAyk/xjEIma6Ah2w/s1600/system_settings_window.png\\"><img style=\\"border-style: none; position: relative;\\" src=\\"http://3.bp.blogspot.com/-1dfq2PSFgwU/UH0orBzZKsI/AAAAAAAAAyk/xjEIma6Ah2w/s1600/system_settings_window.png\\" alt=\\"\\" width=\\"640\\" height=\\"567\\" border=\\"0\\"></a></div>\\n<p><span style=\\"color: #4d4d4d; font-size: 15px; font-family: Times, serif;\\">&nbsp;</span></p>\\n<ul style=\\"padding-right: 2.5em; padding-left: 2.5em; margin-top: 0.5em; margin-bottom: 0.5em; margin-left: 0px; list-style-image: initial; color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px;\\">\\n<li style=\\"margin-bottom: 0.25em; border-style: none;\\"><span style=\\"font-family: Times, serif;\\"><span style=\\"font-size: 16px;\\">Pastaj kliko butonin</span><span style=\\"font-size: 16px;\\">&nbsp;</span><strong style=\\"font-size: 16px;\\">Install/Remove Languages…</strong><span style=\\"font-size: 16px;\\">, zgjidh nga lista gjuhën shqipe (Albanian), dhe kliko</span><span style=\\"font-size: 16px;\\">&nbsp;</span><strong style=\\"font-size: 16px;\\">Apply Changes</strong><span style=\\"font-size: 16px;\\">:</span></span></li>\\n</ul>\\n<p>&nbsp;</p>\\n<div class=\\"separator\\" style=\\"color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;\\"><a style=\\"color: #a30200; margin-left: 1em; margin-right: 1em;\\" href=\\"http://1.bp.blogspot.com/-7ax8o5cpR2A/UH0ol0cwJ-I/AAAAAAAAAx8/Mj7m4cV_wjA/s1600/install_remove_languages.png\\"><img style=\\"border-style: none; position: relative;\\" src=\\"http://1.bp.blogspot.com/-7ax8o5cpR2A/UH0ol0cwJ-I/AAAAAAAAAx8/Mj7m4cV_wjA/s1600/install_remove_languages.png\\" alt=\\"\\" width=\\"640\\" height=\\"552\\" border=\\"0\\"></a></div>\\n<p><span style=\\"color: #4d4d4d; font-family: Times, serif; font-size: 16px;\\"><br></span><span style=\\"color: #4d4d4d; font-size: 15px; font-family: Times, serif;\\"><br></span></p>\\n<ul style=\\"padding-right: 2.5em; padding-left: 2.5em; margin-top: 0.5em; margin-bottom: 0.5em; margin-left: 0px; list-style-image: initial; color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px;\\">\\n<li style=\\"margin-bottom: 0.25em; border-style: none;\\"><span style=\\"font-family: Times, serif;\\"><span style=\\"font-size: 16px;\\">Prit deri sa të shkarkohen dhe të aplikohen të gjitha ndryshimet:</span></span></li>\\n</ul>\\n<p><br style=\\"color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px;\\"><span style=\\"color: #4d4d4d; font-size: 15px; font-family: Times, serif;\\"><br></span></p>\\n<div class=\\"separator\\" style=\\"color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;\\"><a style=\\"color: #a30200; margin-left: 1em; margin-right: 1em;\\" href=\\"http://2.bp.blogspot.com/-eGlksK5n7ms/UH0oigGWoRI/AAAAAAAAAxs/FxmVBmlS6sU/s1600/applying_changes.png\\"><img style=\\"border-style: none; position: relative;\\" src=\\"http://2.bp.blogspot.com/-eGlksK5n7ms/UH0oigGWoRI/AAAAAAAAAxs/FxmVBmlS6sU/s1600/applying_changes.png\\" alt=\\"\\" width=\\"640\\" height=\\"484\\" border=\\"0\\"></a></div>\\n<p><span style=\\"color: #4d4d4d; font-size: 15px; font-family: Times, serif;\\"><br></span><span style=\\"color: #4d4d4d; font-size: 15px; font-family: Times, serif;\\"><br></span></p>\\n<ul style=\\"padding-right: 2.5em; padding-left: 2.5em; margin-top: 0.5em; margin-bottom: 0.5em; margin-left: 0px; list-style-image: initial; color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px;\\">\\n<li style=\\"margin-bottom: 0.25em; border-style: none;\\"><span style=\\"font-family: Times, serif;\\"><span style=\\"font-size: 16px;\\">Tek lista e gjuhëve, gjeje gjuhën</span><span style=\\"font-size: 16px;\\">&nbsp;</span><em style=\\"font-size: 16px;\\">Albanian</em><span style=\\"font-size: 16px;\\">&nbsp;</span><span style=\\"font-size: 16px;\\">(duhet të jetë me ngjyrë gri), tëhiqe me shigjetën e miushit dhe vendose të parën në listë.&nbsp;</span><span style=\\"font-size: 16px;\\">Kliko gjithashtu edhe butonin</span><span style=\\"font-size: 16px;\\">&nbsp;</span><strong style=\\"font-size: 16px;\\">Apply System-Wide</strong><span style=\\"font-size: 16px;\\">. Ndryshimi i gjuhës do të hyj në fuqi pasi të dilni dhe të hyni përsëri në ambjentin e punës.</span></span></li>\\n</ul>\\n<p><br style=\\"color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px;\\"><span style=\\"color: #4d4d4d; font-family: Times, serif; font-size: 16px;\\"><br></span></p>\\n<div class=\\"separator\\" style=\\"color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;\\"><a style=\\"color: #a30200; margin-left: 1em; margin-right: 1em;\\" href=\\"http://3.bp.blogspot.com/-Spq1itMm3iU/UH0onZ4wVPI/AAAAAAAAAyA/wG5j43vDS0s/s1600/language_support_1.png\\"><img style=\\"border-style: none; position: relative;\\" src=\\"http://3.bp.blogspot.com/-Spq1itMm3iU/UH0onZ4wVPI/AAAAAAAAAyA/wG5j43vDS0s/s1600/language_support_1.png\\" alt=\\"\\" width=\\"640\\" height=\\"555\\" border=\\"0\\"></a></div>\\n<div>&nbsp;</div>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'book\' => array(
        \'mlid\' => \'415\',
        \'nid\' => \'8\',
        \'bid\' => \'4\',
        \'menu_name\' => \'book-toc-4\',
        \'plid\' => \'410\',
        \'link_path\' => \'node/8\',
        \'router_path\' => \'node/%\',
        \'link_title\' => \'Vendosja e Gjuhës Shqipe në Ubuntu\',
        \'options\' => array(),
        \'module\' => \'book\',
        \'hidden\' => \'0\',
        \'external\' => \'0\',
        \'has_children\' => \'0\',
        \'expanded\' => \'0\',
        \'weight\' => \'-15\',
        \'depth\' => \'2\',
        \'customized\' => \'0\',
        \'p1\' => \'410\',
        \'p2\' => \'415\',
        \'p3\' => \'0\',
        \'p4\' => \'0\',
        \'p5\' => \'0\',
        \'p6\' => \'0\',
        \'p7\' => \'0\',
        \'p8\' => \'0\',
        \'p9\' => \'0\',
        \'updated\' => \'0\',
        \'href\' => \'node/8\',
        \'title\' => \'Vendosja e Gjuhës Shqipe në Ubuntu\',
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1342860537\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/ubuntu-shqip\',
        \'title\' => \'Vendosja e Gjuhës Shqipe në Ubuntu\',
        \'identifier\' => \'node/8\',
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => array(
        \'pid\' => \'8\',
        \'source\' => \'node/8\',
        \'alias\' => \'ubuntu-shqip\',
        \'language\' => \'en\',
      ),
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'21\',
      \'uid\' => \'1\',
      \'title\' => \'Lista e Projekteve\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'1\',
      \'sticky\' => \'1\',
      \'vuuid\' => \'54441e44-e2e9-a7f4-5d34-df31db40007c\',
      \'nid\' => \'21\',
      \'type\' => \'simplenews\',
      \'language\' => \'en\',
      \'created\' => \'1358841909\',
      \'changed\' => \'1358842370\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'3864bfb1-28e1-0564-5530-dadb87f6bb98\',
      \'revision_timestamp\' => \'1358842370\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<p><span style="font-family: arial, helvetica, sans-serif;">Në fakt, <a title="lista e projekteve të importuara" href="https://l10n.org.al/translations/project/list/*/*/txt" target="_blank">lista e projekteve të importuara</a> është shumë e gjatë, por disa nga më interesantet janë këto: <a title="Fjalori" href="https://l10n.org.al/translations/search?project=vocabulary&amp;lng=sq" target="_blank">Fjalori</a>, <a title="Pingus" href="https://l10n.org.al/translations/search?project=pingus&amp;lng=sq" target="_blank">Pingus</a>, <a title="KTurtle" href="https://l10n.org.al/translations/search?project=kturtle&amp;lng=sq" target="_blank">KTurtle</a>, <a title="Udhëzuesi i KTurtle" href="https://l10n.org.al/translations/search?project=doc_kdeedu_kturtle&amp;lng=sq" target="_blank">Udhëzuesi i KTurtle</a>, <a title="B-Translator" href="https://l10n.org.al/translations/search?project=btranslator&amp;lng=sq" target="_blank">B-Translator</a>, <a title="LibreOffice/Writter" href="https://l10n.org.al/translations/search?origin=LibreOffice&amp;project=sw&amp;lng=sq" target="_blank">LibreOffice/Writter</a>, <a title="Mozilla/Browser" href="https://l10n.org.al/translations/search?origin=Mozilla&amp;project=browser&amp;lng=sq" target="_blank">Mozilla/Browser</a>, <a title="FirefoxOS" href="https://l10n.org.al/translations/search?origin=FirefoxOS&amp;project=Gaia&amp;lng=sq" target="_blank">FirefoxOS</a>, <a title="WordPress" href="https://l10n.org.al/translations/search?origin=WordPress&amp;project=wp-sq&amp;lng=sq" target="_blank">WordPress</a>, etj.<!--break--></span></p>\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Në fakt, <a title=\\"lista e projekteve të importuara\\" href=\\"https://l10n.org.al/translations/project/list/*/*/txt\\" target=\\"_blank\\">lista e projekteve të importuara</a> është shumë e gjatë, por disa nga më interesantet janë këto: <a title=\\"Fjalori\\" href=\\"https://l10n.org.al/translations/search?project=vocabulary&amp;lng=sq\\" target=\\"_blank\\">Fjalori</a>, <a title=\\"Pingus\\" href=\\"https://l10n.org.al/translations/search?project=pingus&amp;lng=sq\\" target=\\"_blank\\">Pingus</a>, <a title=\\"KTurtle\\" href=\\"https://l10n.org.al/translations/search?project=kturtle&amp;lng=sq\\" target=\\"_blank\\">KTurtle</a>, <a title=\\"Udhëzuesi i KTurtle\\" href=\\"https://l10n.org.al/translations/search?project=doc_kdeedu_kturtle&amp;lng=sq\\" target=\\"_blank\\">Udhëzuesi i KTurtle</a>, <a title=\\"B-Translator\\" href=\\"https://l10n.org.al/translations/search?project=btranslator&amp;lng=sq\\" target=\\"_blank\\">B-Translator</a>, <a title=\\"LibreOffice/Writter\\" href=\\"https://l10n.org.al/translations/search?origin=LibreOffice&amp;project=sw&amp;lng=sq\\" target=\\"_blank\\">LibreOffice/Writter</a>, <a title=\\"Mozilla/Browser\\" href=\\"https://l10n.org.al/translations/search?origin=Mozilla&amp;project=browser&amp;lng=sq\\" target=\\"_blank\\">Mozilla/Browser</a>, <a title=\\"FirefoxOS\\" href=\\"https://l10n.org.al/translations/search?origin=FirefoxOS&amp;project=Gaia&amp;lng=sq\\" target=\\"_blank\\">FirefoxOS</a>, <a title=\\"WordPress\\" href=\\"https://l10n.org.al/translations/search?origin=WordPress&amp;project=wp-sq&amp;lng=sq\\" target=\\"_blank\\">WordPress</a>, etj.</p>\\n<!--break--><p></span></p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_simplenews_term\' => array(
        \'en\' => array(
          array(
            \'tid\' => \'3\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1358841909\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/node/21\',
        \'title\' => \'Lista e Projekteve\',
        \'identifier\' => \'node/21\',
      ),
      \'simplenews\' => (object) array(
          \'nid\' => \'21\',
          \'tid\' => \'3\',
          \'status\' => \'2\',
          \'sent_subscriber_count\' => \'31\',
          \'name\' => \'Njoftime\',
          \'description\' => \'Njoftime të brendëshme për personat e rregjistruar te Përkthimi i Programeve në Shqip.\',
          \'weight\' => \'0\',
        ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'14\',
      \'uid\' => \'1\',
      \'title\' => \'Statistika rreth aktivitetit të kontribuesve\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'d8d3c58b-19ae-ec84-65b9-e2e060879d6f\',
      \'nid\' => \'14\',
      \'type\' => \'simplenews\',
      \'language\' => \'en\',
      \'created\' => \'1352417142\',
      \'changed\' => \'1352417320\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'4968d69c-86f2-3f34-89b5-d29fca5789e5\',
      \'revision_timestamp\' => \'1352417320\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<p>Përshëndetje,</p><p>Me pak vonesë, por më në fund janë instaluar në faqe edhe disa statistika të thjeshta rreth aktivitetit të kontribuesve (të cilat duken në anën e majtë të faqes, si dhe te paneli).</p><p>Vetëm se jam në mëdyshje, a ti lë të dukshme për të gjithë, apo vetëm për anëtarët e rregjistruar? Po qe se keni ndonjë mendim, më çoni ndonjë email.</p><p>Dashamiri</p>\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p>Përshëndetje,</p>\\n<p>Me pak vonesë, por më në fund janë instaluar në faqe edhe disa statistika të thjeshta rreth aktivitetit të kontribuesve (të cilat duken në anën e majtë të faqes, si dhe te paneli).</p>\\n<p>Vetëm se jam në mëdyshje, a ti lë të dukshme për të gjithë, apo vetëm për anëtarët e rregjistruar? Po qe se keni ndonjë mendim, më çoni ndonjë email.</p>\\n<p>Dashamiri</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_simplenews_term\' => array(
        \'en\' => array(
          array(
            \'tid\' => \'3\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1352417142\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/node/14\',
        \'title\' => \'Statistika rreth aktivitetit të kontribuesve\',
        \'identifier\' => \'node/14\',
      ),
      \'simplenews\' => (object) array(
          \'nid\' => \'14\',
          \'tid\' => \'3\',
          \'status\' => \'2\',
          \'sent_subscriber_count\' => \'25\',
          \'name\' => \'Njoftime\',
          \'description\' => \'Njoftime të brendëshme për personat e rregjistruar te Përkthimi i Programeve në Shqip.\',
          \'weight\' => \'0\',
        ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'11\',
      \'uid\' => \'1\',
      \'title\' => \'Server i ri për l10n.org.al\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'1\',
      \'sticky\' => \'1\',
      \'vuuid\' => \'bbb5e7e8-abd5-c2a4-012a-c02a137cf93c\',
      \'nid\' => \'11\',
      \'type\' => \'blog\',
      \'language\' => \'en\',
      \'created\' => \'1344084571\',
      \'changed\' => \'1358642227\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'49b78206-03ca-5ee4-495b-2399d781c5bd\',
      \'revision_timestamp\' => \'1358642227\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<p><span style="font-family: arial, sans-serif; line-height: normal;">Meqënëse</span><span style="font-family: arial, sans-serif; line-height: normal;">&nbsp;<em>amazon.com</em> ma kishte sjellë në majë të hundës me problemet e shpeshta, e kam fikur serverin&nbsp;</span><span style="font-family: arial, sans-serif; line-height: normal;">te <em>amazon.com</em> dhe kam blerë një server tjetër te <em>rackspace.com</em> . Ky server ka <strong>512MB RAM</strong></span><span style="font-family: arial, sans-serif; line-height: normal;">&nbsp;dhe <strong>20GB</strong> disk, dhe më kushton afro <strong>20-25$</strong> në muaj. Më shtrenjtë se <em>Amazon</em>,&nbsp;</span><span style="font-family: arial, sans-serif; line-height: normal;">por të paktën shpresoj të jetë më i qëndrueshëm.<!--break--></span></p><p><span style="font-family: arial, sans-serif; line-height: normal;">Ndërkohë, nga kërkimet që kam bërë në internet, më del se <strong>512MB RAM</strong></span><span style="font-family: arial, sans-serif; line-height: normal;">&nbsp;është minimumi i kërkesave për Drupalin. Pra e mira do ishte që të kishim një server&nbsp;</span><span style="font-family: arial, sans-serif; line-height: normal;">me të paktën <strong>1GB RAM</strong>, për një punë normale të aplikacionit. Një server</span><span style="font-family: arial, sans-serif; line-height: normal;">&nbsp;i tillë te <em>Rackspace</em> kushton gati dyfish (rreth <strong>40-50$</strong>), por do shikoj&nbsp;</span><span style="font-family: arial, sans-serif; line-height: normal;">ndonjë mënyrë</span><span style="font-family: arial, sans-serif; line-height: normal;">&nbsp;në të ardhmen për të siguruar fondet e nevojshme.<br></span></p><p><span style="font-family: arial, sans-serif; line-height: normal;">Një mundësi do të ishte që të krijohej ndonjë shoqatë jofitimprurëse për përkthimin e programeve në shqip, dhe kuotat e anëtarëve (p.sh. <strong>5 EUR</strong> në muaj) të përdoreshin për të mbuluar shpenzimet e nevojshme. Por nuk jam i sigurtë nëse do të gjejë mbështetje të mjaftueshme kjo ide, dhe gjithashtu nuk kam kohë dhe nerva që të merrem me organizimin e një shoqate të tillë, si dhe me dokumentacionin e nevojshëm për legalizimin e saj. Shpresoj që ndonjëri ta marr përsipër këtë punë, sepse në fakt objektivi dhe qëllimet e shoqatës janë mjaft të qarta dhe të sakta.</span></p>\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p><span style=\\"font-family: arial, sans-serif; line-height: normal;\\">Meqënëse</span><span style=\\"font-family: arial, sans-serif; line-height: normal;\\">&nbsp;<em>amazon.com</em> ma kishte sjellë në majë të hundës me problemet e shpeshta, e kam fikur serverin&nbsp;</span><span style=\\"font-family: arial, sans-serif; line-height: normal;\\">te <em>amazon.com</em> dhe kam blerë një server tjetër te <em>rackspace.com</em> . Ky server ka <strong>512MB RAM</strong></span><span style=\\"font-family: arial, sans-serif; line-height: normal;\\">&nbsp;dhe <strong>20GB</strong> disk, dhe më kushton afro <strong>20-25$</strong> në muaj. Më shtrenjtë se <em>Amazon</em>,&nbsp;</span><span style=\\"font-family: arial, sans-serif; line-height: normal;\\">por të paktën shpresoj të jetë më i qëndrueshëm.</p>\\n<!--break--><p></span></p>\\n<p><span style=\\"font-family: arial, sans-serif; line-height: normal;\\">Ndërkohë, nga kërkimet që kam bërë në internet, më del se <strong>512MB RAM</strong></span><span style=\\"font-family: arial, sans-serif; line-height: normal;\\">&nbsp;është minimumi i kërkesave për Drupalin. Pra e mira do ishte që të kishim një server&nbsp;</span><span style=\\"font-family: arial, sans-serif; line-height: normal;\\">me të paktën <strong>1GB RAM</strong>, për një punë normale të aplikacionit. Një server</span><span style=\\"font-family: arial, sans-serif; line-height: normal;\\">&nbsp;i tillë te <em>Rackspace</em> kushton gati dyfish (rreth <strong>40-50$</strong>), por do shikoj&nbsp;</span><span style=\\"font-family: arial, sans-serif; line-height: normal;\\">ndonjë mënyrë</span><span style=\\"font-family: arial, sans-serif; line-height: normal;\\">&nbsp;në të ardhmen për të siguruar fondet e nevojshme.<br></span></p>\\n<p><span style=\\"font-family: arial, sans-serif; line-height: normal;\\">Një mundësi do të ishte që të krijohej ndonjë shoqatë jofitimprurëse për përkthimin e programeve në shqip, dhe kuotat e anëtarëve (p.sh. <strong>5 EUR</strong> në muaj) të përdoreshin për të mbuluar shpenzimet e nevojshme. Por nuk jam i sigurtë nëse do të gjejë mbështetje të mjaftueshme kjo ide, dhe gjithashtu nuk kam kohë dhe nerva që të merrem me organizimin e një shoqate të tillë, si dhe me dokumentacionin e nevojshëm për legalizimin e saj. Shpresoj që ndonjëri ta marr përsipër këtë punë, sepse në fakt objektivi dhe qëllimet e shoqatës janë mjaft të qarta dhe të sakta.</span></p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Post\',
          \'sioct:BlogPost\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1344084571\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/node/11\',
        \'title\' => \'Server i ri për l10n.org.al\',
        \'identifier\' => \'node/11\',
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'13\',
      \'uid\' => \'1\',
      \'title\' => \'Projekte të tjera të importuara (Drupal, WordPress, B-Translator)\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'ae2990c9-4e47-6c84-a1f3-1effdc8aca28\',
      \'nid\' => \'13\',
      \'type\' => \'simplenews\',
      \'language\' => \'en\',
      \'created\' => \'1350005320\',
      \'changed\' => \'1350005490\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'4a782647-1863-ca04-c152-0ff21b3f91f6\',
      \'revision_timestamp\' => \'1350005490\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<p>Përshëndetje miq,</p><p>Kam përfunduar tashmë edhe importimin e <em>Drupal</em> core dhe disa moduleve të tjera (ato që janë instaluar te faqja e btranslator):</p><ul><li>https://l10n.org.al/translations/project/list/Drupal/*/txt</li><li>https://l10n.org.al/translations/search?lng=sq&amp;origin=Drupal&amp;limit=10</li></ul><p>Kush të jetë i interesuar për të rishikuar përkthimet e Drupal-it, mund ta zgjedhë këtë te preferencat e tij.</p><p>Vini re gjithashtu se midis moduleve të Drupal-it janë edhe <strong>Drupal/btranslator</strong> dhe&nbsp;<strong>Drupal/l10n_feedback</strong>, të cilat shërbejnë për përkthimin në shqip të vetë <em>Përkthyesit-B</em>:</p><ul><li>https://l10n.org.al/translations/search?lng=sq&amp;project=btranslator&amp;limit=10</li><li>https://l10n.org.al/translations/search?lng=sq&amp;project=l10n_feedback&amp;limit=10</li></ul><p>Pothuajse të gjitha vargjet janë të pa përkthyera. A është i gatshëm ndokush të ndihmojë për përkthimin e tyre?</p><p>Meqë ra fjala, kam pasur kërkesa edhe për importimin e përkthimeve të <em>WordPress</em>-it:</p><ul><li>https://l10n.org.al/translations/search?lng=sq&amp;project=wp-sq&amp;limit=10</li></ul><p>Gjithë të mirat,</p><p>Dashamiri</p><div>&nbsp;</div>\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p>Përshëndetje miq,</p>\\n<p>Kam përfunduar tashmë edhe importimin e <em>Drupal</em> core dhe disa moduleve të tjera (ato që janë instaluar te faqja e btranslator):</p>\\n<ul>\\n<li><a href=\\"https://l10n.org.al/translations/project/list/Drupal/*/txt\\">https://l10n.org.al/translations/project/list/Drupal/*/txt</a></li>\\n<li><a href=\\"https://l10n.org.al/translations/search?lng=sq&amp;origin=Drupal&amp;limit=10\\">https://l10n.org.al/translations/search?lng=sq&amp;origin=Drupal&amp;limit=10</a></li>\\n</ul>\\n<p>Kush të jetë i interesuar për të rishikuar përkthimet e Drupal-it, mund ta zgjedhë këtë te preferencat e tij.</p>\\n<p>Vini re gjithashtu se midis moduleve të Drupal-it janë edhe <strong>Drupal/btranslator</strong> dhe&nbsp;<strong>Drupal/l10n_feedback</strong>, të cilat shërbejnë për përkthimin në shqip të vetë <em>Përkthyesit-B</em>:</p>\\n<ul>\\n<li><a href=\\"https://l10n.org.al/translations/search?lng=sq&amp;project=btranslator&amp;limit=10\\">https://l10n.org.al/translations/search?lng=sq&amp;project=btranslator&amp;limit=10</a></li>\\n<li><a href=\\"https://l10n.org.al/translations/search?lng=sq&amp;project=l10n_feedback&amp;limit=10\\">https://l10n.org.al/translations/search?lng=sq&amp;project=l10n_feedback&amp;lim...</a></li>\\n</ul>\\n<p>Pothuajse të gjitha vargjet janë të pa përkthyera. A është i gatshëm ndokush të ndihmojë për përkthimin e tyre?</p>\\n<p>Meqë ra fjala, kam pasur kërkesa edhe për importimin e përkthimeve të <em>WordPress</em>-it:</p>\\n<ul>\\n<li><a href=\\"https://l10n.org.al/translations/search?lng=sq&amp;project=wp-sq&amp;limit=10\\">https://l10n.org.al/translations/search?lng=sq&amp;project=wp-sq&amp;limit=10</a></li>\\n</ul>\\n<p>Gjithë të mirat,</p>\\n<p>Dashamiri</p>\\n<div>&nbsp;</div>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_simplenews_term\' => array(
        \'en\' => array(
          array(
            \'tid\' => \'3\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1350005320\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/node/13\',
        \'title\' => \'Projekte të tjera të importuara (Drupal, WordPress, B-Translator)\',
        \'identifier\' => \'node/13\',
      ),
      \'simplenews\' => (object) array(
          \'nid\' => \'13\',
          \'tid\' => \'3\',
          \'status\' => \'2\',
          \'sent_subscriber_count\' => \'17\',
          \'name\' => \'Njoftime\',
          \'description\' => \'Njoftime të brendëshme për personat e rregjistruar te Përkthimi i Programeve në Shqip.\',
          \'weight\' => \'0\',
        ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'4\',
      \'uid\' => \'1\',
      \'title\' => \'Udhëzuesi i Përkthyesit\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'4338fea8-e287-ec74-39da-2d27df55e8b2\',
      \'nid\' => \'4\',
      \'type\' => \'book\',
      \'language\' => \'en\',
      \'created\' => \'1342858331\',
      \'changed\' => \'1342858331\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'54e1eada-a66a-a404-6598-d8dd480fa6f6\',
      \'revision_timestamp\' => \'1342858331\',
      \'revision_uid\' => \'1\',
      \'body\' => array(),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'book\' => array(
        \'mlid\' => \'410\',
        \'nid\' => \'4\',
        \'bid\' => \'4\',
        \'menu_name\' => \'book-toc-4\',
        \'plid\' => \'0\',
        \'link_path\' => \'node/4\',
        \'router_path\' => \'node/%\',
        \'link_title\' => \'Udhëzuesi i Përkthyesit\',
        \'options\' => array(),
        \'module\' => \'book\',
        \'hidden\' => \'0\',
        \'external\' => \'0\',
        \'has_children\' => \'1\',
        \'expanded\' => \'0\',
        \'weight\' => \'0\',
        \'depth\' => \'1\',
        \'customized\' => \'0\',
        \'p1\' => \'410\',
        \'p2\' => \'0\',
        \'p3\' => \'0\',
        \'p4\' => \'0\',
        \'p5\' => \'0\',
        \'p6\' => \'0\',
        \'p7\' => \'0\',
        \'p8\' => \'0\',
        \'p9\' => \'0\',
        \'updated\' => \'0\',
        \'href\' => \'node/4\',
        \'title\' => \'Udhëzuesi i Përkthyesit\',
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1342858331\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/udhezuesi\',
        \'title\' => \'Udhëzuesi i Përkthyesit\',
        \'identifier\' => \'node/4\',
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => array(
        \'pid\' => \'4\',
        \'source\' => \'node/4\',
        \'alias\' => \'udhezuesi\',
        \'language\' => \'en\',
      ),
      \'menu\' => array(
        \'link_title\' => \'Udhëzuesi i Përkthyesit\',
        \'mlid\' => 0,
        \'plid\' => \'0\',
        \'menu_name\' => \'main-menu\',
        \'weight\' => \'-48\',
        \'options\' => array(),
        \'module\' => \'menu\',
        \'expanded\' => \'0\',
        \'hidden\' => \'0\',
        \'has_children\' => \'0\',
        \'customized\' => 0,
        \'parent_depth_limit\' => 8,
        \'description\' => \'\',
        \'enabled\' => 1,
      ),
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'17\',
      \'uid\' => \'1\',
      \'title\' => \'Korrigjimi i përkthimeve\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'1\',
      \'sticky\' => \'1\',
      \'vuuid\' => \'35bd1a04-129d-90c4-7929-bd304f6c01d6\',
      \'nid\' => \'17\',
      \'type\' => \'simplenews\',
      \'language\' => \'en\',
      \'created\' => \'1354172108\',
      \'changed\' => \'1358642410\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'5b0961ff-3dc8-bff4-a9fe-8207d8e7bc3f\',
      \'revision_timestamp\' => \'1358642410\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<p><span style="font-family: arial, helvetica, sans-serif;">Autori i një përkthimi ka mundësi ta korrigjoj atë, duke sugjeruar një përkthim tjetër (sugjerimi i dytë mbishkruan të parin). Kjo të jep mundësi që të bësh korrigjimin e gabimeve të vogla, pa qenë nevoja për të shtuar një përkthim tjetër (i cili ndryshon nga i mëparshmi vetëm me disa shkronja).<!--break--></span></p><p><span style="font-family: arial, helvetica, sans-serif;">Kur bëhet një korrigjim, votuesit e përkthimit të mëparshëm (nëse ka të tillë) njoftohen për ndryshimin e bërë, me qëllim që ta rishikojnë atë, dhe po të jetë nevoja ta ndryshojnë votën e tyre.</span></p>\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Autori i një përkthimi ka mundësi ta korrigjoj atë, duke sugjeruar një përkthim tjetër (sugjerimi i dytë mbishkruan të parin). Kjo të jep mundësi që të bësh korrigjimin e gabimeve të vogla, pa qenë nevoja për të shtuar një përkthim tjetër (i cili ndryshon nga i mëparshmi vetëm me disa shkronja).</p>\\n<!--break--><p></span></p>\\n<p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Kur bëhet një korrigjim, votuesit e përkthimit të mëparshëm (nëse ka të tillë) njoftohen për ndryshimin e bërë, me qëllim që ta rishikojnë atë, dhe po të jetë nevoja ta ndryshojnë votën e tyre.</span></p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_simplenews_term\' => array(
        \'en\' => array(
          array(
            \'tid\' => \'3\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1354172108\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/node/17\',
        \'title\' => \'Korrigjimi i përkthimeve\',
        \'identifier\' => \'node/17\',
      ),
      \'simplenews\' => (object) array(
          \'nid\' => \'17\',
          \'tid\' => \'3\',
          \'status\' => \'2\',
          \'sent_subscriber_count\' => \'31\',
          \'name\' => \'Njoftime\',
          \'description\' => \'Njoftime të brendëshme për personat e rregjistruar te Përkthimi i Programeve në Shqip.\',
          \'weight\' => \'0\',
        ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'1\',
      \'uid\' => \'1\',
      \'title\' => \'Visualization of Translating GNOME Into Albanian\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'2\',
      \'promote\' => \'1\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'5b1deb0c-025f-a224-1ddd-1e43ecdba832\',
      \'nid\' => \'1\',
      \'type\' => \'blog\',
      \'language\' => \'en\',
      \'created\' => \'1342857961\',
      \'changed\' => \'1358642637\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'5ec869e5-1366-dc84-65c5-1dde8246aae7\',
      \'revision_timestamp\' => \'1358642637\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "<p><iframe class=\\"youtube-player\\" src=\\"https://www.youtube.com/embed/ThZoTGBB-m8\\" frameborder=\\"0\\" width=\\"640\\" height=\\"385\\"></iframe></p><p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Recently I generated this video that shows the activity of translating GNOME projects into Albanian during the last years. This visualization was generated by Gource <a href=\\"https://code.google.com/p/gource/\\">https://code.google.com/p/gource/</a> .</span></p><p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Gource is very easy to use, just install it: <strong>apt-get install gource</strong>, go to the project directory, and type: <strong>gource</strong>. However, in the case of GNOME translations this does not generate something useful. The problem is not with gource but rather with the structure of the projects. Each translation project has its own repository, so it is not easy to generate a general view for all the projects. Besides this, each translation project has data for all the languages, and I would like to visualize only the data about the Albanian translations.</span></p><p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Here I describe the steps and data processing that I did to generate this visualization.</span></p><ol><li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Checkout all the GNOME projects (translation files):</span><pre><span style=\\"font-family: arial, helvetica, sans-serif;\\">mkdir GNOME/\\r\\ncd GNOME/\\r\\nsvn_gnome=http://svn.gnome.org\\r\\ngnome_modules=$(wget -o /dev/null -O- $svn_gnome/viewvc/ | grep \'a href=\\"/viewvc/[^\\"]\' | sed \'s#.*/viewvc/\\\\([^/]*\\\\)/.*#\\\\1#\')\\r\\nfor module in $gnome_modules; do svn checkout $svn_gnome/svn/$module/trunk/po $module; done\\r\\ncd .. </span></pre></li><li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Generate gource log files for each of the projects:</span><pre><span style=\\"font-family: arial, helvetica, sans-serif;\\">for dir in $(ls GNOME/); do echo $dir; cd GNOME/$dir/; gource --output-custom-log $dir.log; done\\r\\n</span></pre></li><li><span style=\\"font-family: arial, helvetica, sans-serif;\\">For each log file replace the word <em>trunk</em>with the name of the project (name of the directory), and concatenate all of them in a single big file:</span><pre><span style=\\"font-family: arial, helvetica, sans-serif;\\">find GNOME -name \'*.log\' &gt; gnome_log.txt\\r\\nfor file in $(find GNOME/ -name \'*.log\'); do echo $file; dir=$(dirname $file); cat $file | sed -e \\"s,/trunk/,/$dir/,\\" &gt;&gt; GNOME.log; done\\r\\n</span></pre></li><li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Now extract all the log lines related to Albanian translations:</span><pre><span style=\\"font-family: arial, helvetica, sans-serif;\\">cat GNOME.log | grep \\"sq.po\\" &gt; GNOME_sq.log\\r\\n</span></pre></li><li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Remove the directory <em>/po/</em>from the names of the files inside the logs:</span><pre><span style=\\"font-family: arial, helvetica, sans-serif;\\">sed -e \'s,/po/.*,,\' -i GNOME_sq.log\\r\\n</span></pre></li><li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Order them according to the time of the file modification:</span><pre><span style=\\"font-family: arial, helvetica, sans-serif;\\">sort -t\'|\' -k 1,1n -o GNOME.sq.log GNOME_sq.log\\r\\nrm GNOME_sq.log\\r\\n</span></pre></li><li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Create the visualization movie with gource and transform it in a suitable format for uploading to YouTube:</span><pre><span style=\\"font-family: arial, helvetica, sans-serif;\\">gource GNOME.sq.log -s 0.1 -i 0 --max-files 0 --date-format \\"%B %Y\\" -640x360 -o - \\\\ \\r\\n  | ffmpeg -y -r 25 -f image2pipe -vcodec ppm -i - -vcodec libvpx -b 10000K GNOME.sq.webm\\r\\n</span></pre></li></ol>",
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p><iframe class=\\"youtube-player\\" src=\\"https://www.youtube.com/embed/ThZoTGBB-m8\\" frameborder=\\"0\\" width=\\"640\\" height=\\"385\\"></iframe></p>\\n<p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Recently I generated this video that shows the activity of translating GNOME projects into Albanian during the last years. This visualization was generated by Gource <a href=\\"https://code.google.com/p/gource/\\">https://code.google.com/p/gource/</a> .</span></p>\\n<p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Gource is very easy to use, just install it: <strong>apt-get install gource</strong>, go to the project directory, and type: <strong>gource</strong>. However, in the case of GNOME translations this does not generate something useful. The problem is not with gource but rather with the structure of the projects. Each translation project has its own repository, so it is not easy to generate a general view for all the projects. Besides this, each translation project has data for all the languages, and I would like to visualize only the data about the Albanian translations.</span></p>\\n<p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Here I describe the steps and data processing that I did to generate this visualization.</span></p>\\n<ol>\\n<li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Checkout all the GNOME projects (translation files):</span></p>\\n<pre><span style=\\"font-family: arial, helvetica, sans-serif;\\">mkdir GNOME/\\ncd GNOME/\\nsvn_gnome=http://svn.gnome.org\\ngnome_modules=$(wget -o /dev/null -O- $svn_gnome/viewvc/ | grep \'a href=\\"/viewvc/[^\\"]\' | sed \'s#.*/viewvc/\\\\([^/]*\\\\)/.*#\\\\1#\')\\nfor module in $gnome_modules; do svn checkout $svn_gnome/svn/$module/trunk/po $module; done\\ncd .. </span></pre></li>\\n<li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Generate gource log files for each of the projects:</span><br />\\n<pre><span style=\\"font-family: arial, helvetica, sans-serif;\\">for dir in $(ls GNOME/); do echo $dir; cd GNOME/$dir/; gource --output-custom-log $dir.log; done\\n</span></pre></li>\\n<li><span style=\\"font-family: arial, helvetica, sans-serif;\\">For each log file replace the word <em>trunk</em>with the name of the project (name of the directory), and concatenate all of them in a single big file:</span><br />\\n<pre><span style=\\"font-family: arial, helvetica, sans-serif;\\">find GNOME -name \'*.log\' &gt; gnome_log.txt\\nfor file in $(find GNOME/ -name \'*.log\'); do echo $file; dir=$(dirname $file); cat $file | sed -e \\"s,/trunk/,/$dir/,\\" &gt;&gt; GNOME.log; done\\n</span></pre></li>\\n<li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Now extract all the log lines related to Albanian translations:</span><br />\\n<pre><span style=\\"font-family: arial, helvetica, sans-serif;\\">cat GNOME.log | grep \\"sq.po\\" &gt; GNOME_sq.log\\n</span></pre></li>\\n<li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Remove the directory <em>/po/</em>from the names of the files inside the logs:</span><br />\\n<pre><span style=\\"font-family: arial, helvetica, sans-serif;\\">sed -e \'s,/po/.*,,\' -i GNOME_sq.log\\n</span></pre></li>\\n<li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Order them according to the time of the file modification:</span><br />\\n<pre><span style=\\"font-family: arial, helvetica, sans-serif;\\">sort -t\'|\' -k 1,1n -o GNOME.sq.log GNOME_sq.log\\nrm GNOME_sq.log\\n</span></pre></li>\\n<li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Create the visualization movie with gource and transform it in a suitable format for uploading to YouTube:</span><br />\\n<pre><span style=\\"font-family: arial, helvetica, sans-serif;\\">gource GNOME.sq.log -s 0.1 -i 0 --max-files 0 --date-format \\"%B %Y\\" -640x360 -o - \\\\ \\n  | ffmpeg -y -r 25 -f image2pipe -vcodec ppm -i - -vcodec libvpx -b 10000K GNOME.sq.webm\\n</span></pre></li>\\n</ol>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Post\',
          \'sioct:BlogPost\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1342857961\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/Visualization-of-Translating-GNOME-Into-Albanian\',
        \'title\' => \'Visualization of Translating GNOME Into Albanian\',
        \'identifier\' => \'node/1\',
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => array(
        \'pid\' => \'1\',
        \'source\' => \'node/1\',
        \'alias\' => \'Visualization-of-Translating-GNOME-Into-Albanian\',
        \'language\' => \'en\',
      ),
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'16\',
      \'uid\' => \'1\',
      \'title\' => \'Përkthimi i FirefoxOS\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'5f265ffa-7661-1c74-71eb-374031207d09\',
      \'nid\' => \'16\',
      \'type\' => \'simplenews\',
      \'language\' => \'en\',
      \'created\' => \'1353025765\',
      \'changed\' => \'1353025882\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'697dde67-a296-0e14-e5ba-a3a3bc96f05c\',
      \'revision_timestamp\' => \'1353025882\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<p>Besniku ka përfunduar përkthimin në shqip të FirefoxOS (sistem pune për celularët, si Android dhe iOS) dhe dëshiron që tu bëjë një rishikim përkthimeve. Njoftimin origjinal mund ta lexoni këtu:&nbsp;https://groups.google.com/d/topic/open-labs-albania/WVn7NxR80eY/discussion</p><p>Meqënëse unë i kam importuar përkthimet te B-Translator (shiko&nbsp;<a href="https://l10n.org.al/translations/search?lng=sq&amp;origin=FirefoxOS&amp;limit=10">https://l10n.org.al/translations/search?lng=sq&amp;origin=FirefoxOS&amp;limit=10</a>) mund ta bëjmë rishikimin edhe këtu. Kush është i interesuar që të ndihmojë, mund të zgjedhe FirefoxOS si projektin&nbsp;e preferuar, në mënyrë që sistemi ti paraqesë vargje vetëm nga ky projekt. Për më shumë detaje mund të shikoni edhe këtë diskutim:&nbsp;https://groups.google.com/d/topic/btranslator/2e5-PfNty8Q/discussion</p>\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p>Besniku ka përfunduar përkthimin në shqip të FirefoxOS (sistem pune për celularët, si Android dhe iOS) dhe dëshiron që tu bëjë një rishikim përkthimeve. Njoftimin origjinal mund ta lexoni këtu:&nbsp;<a href=\\"https://groups.google.com/d/topic/open-labs-albania/WVn7NxR80eY/discussion\\">https://groups.google.com/d/topic/open-labs-albania/WVn7NxR80eY/discussion</a></p>\\n<p>Meqënëse unë i kam importuar përkthimet te B-Translator (shiko&nbsp;<a href=\\"https://l10n.org.al/translations/search?lng=sq&amp;origin=FirefoxOS&amp;limit=10\\">https://l10n.org.al/translations/search?lng=sq&amp;origin=FirefoxOS&amp;limit=10</a>) mund ta bëjmë rishikimin edhe këtu. Kush është i interesuar që të ndihmojë, mund të zgjedhe FirefoxOS si projektin&nbsp;e preferuar, në mënyrë që sistemi ti paraqesë vargje vetëm nga ky projekt. Për më shumë detaje mund të shikoni edhe këtë diskutim:&nbsp;<a href=\\"https://groups.google.com/d/topic/btranslator/2e5-PfNty8Q/discussion\\">https://groups.google.com/d/topic/btranslator/2e5-PfNty8Q/discussion</a></p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_simplenews_term\' => array(
        \'en\' => array(
          array(
            \'tid\' => \'3\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1353025765\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/node/16\',
        \'title\' => \'Përkthimi i FirefoxOS\',
        \'identifier\' => \'node/16\',
      ),
      \'simplenews\' => (object) array(
          \'nid\' => \'16\',
          \'tid\' => \'3\',
          \'status\' => \'2\',
          \'sent_subscriber_count\' => \'30\',
          \'name\' => \'Njoftime\',
          \'description\' => \'Njoftime të brendëshme për personat e rregjistruar te Përkthimi i Programeve në Shqip.\',
          \'weight\' => \'0\',
        ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'12\',
      \'uid\' => \'1\',
      \'title\' => \'Edit profiles and Invitations\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'945d6e7c-2810-c3d4-196e-1a70f2f1fc8f\',
      \'nid\' => \'12\',
      \'type\' => \'simplenews\',
      \'language\' => \'en\',
      \'created\' => \'1349510621\',
      \'changed\' => \'1349510809\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'6d29a99d-d474-db14-11e8-81f0bf2e0215\',
      \'revision_timestamp\' => \'1349510809\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "<p>Përshëndetje [simplenews-subscriber:user:name],</p><p>Ky është njoftimi i parë (newsletter) nga Përkthimi i Programeve në Shqip, i cili u dërgohet të gjithë anëtarëve të rregjistruar në sistem. Qëllimi është për tju vënë në dijeni lidhur me zhvillimet e fundit.</p><p>Së pari, te <a title=\\"Edit Profile\\" href=\\"https://l10n.org.al/user/[simplenews-subscriber:user:uid]/edit-profile\\" target=\\"_blank\\">Edit Profiles</a> mund të zgjidhni një ose disa projekte të preferuara dhe sistemi do t\'i përzgjedhë vargjet për ju vetëm nga këto projekte. Po ashtu mund të caktoni edhe rradhën e përzgjedhjes së vargjeve (p.sh. e rastësishme ose sipas rradhës). Kurse përzgjedhjet e tjera (gjuhët ndihmëse, mënyrat e votimit, etj.) për momentin nuk janë funksionale.</p><p>Anëtarët e rinj me siguri i kanë vënë re këto mundësi, meqënëse shfaqen qysh në rregjistrim, por anëtarëve të hershëm ndoshta mund t\'u kenë shpëtuar.</p><p>Një gjë tjetër e shtuar kohët e fundit është edhe mundësia për të dërguar ftesa (<a title=\\"Invitations\\" href=\\"https://l10n.org.al/user/[simplenews-subscriber:user:uid]/invites\\" target=\\"_blank\\">Invitations</a>), me anë të së cilës mund të ftoni njerëzit e njohur, mjafton që t\'u dini adresën email.</p><p>Kaq për këtë rradhë. Mbetshi me të mira.</p><p>Dashamiri</p><p>&nbsp;</p>",
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p>Përshëndetje [simplenews-subscriber:user:name],</p>\\n<p>Ky është njoftimi i parë (newsletter) nga Përkthimi i Programeve në Shqip, i cili u dërgohet të gjithë anëtarëve të rregjistruar në sistem. Qëllimi është për tju vënë në dijeni lidhur me zhvillimet e fundit.</p>\\n<p>Së pari, te <a title=\\"Edit Profile\\" href=\\"https://l10n.org.al/user/[simplenews-subscriber:user:uid]/edit-profile\\" target=\\"_blank\\">Edit Profiles</a> mund të zgjidhni një ose disa projekte të preferuara dhe sistemi do t\'i përzgjedhë vargjet për ju vetëm nga këto projekte. Po ashtu mund të caktoni edhe rradhën e përzgjedhjes së vargjeve (p.sh. e rastësishme ose sipas rradhës). Kurse përzgjedhjet e tjera (gjuhët ndihmëse, mënyrat e votimit, etj.) për momentin nuk janë funksionale.</p>\\n<p>Anëtarët e rinj me siguri i kanë vënë re këto mundësi, meqënëse shfaqen qysh në rregjistrim, por anëtarëve të hershëm ndoshta mund t\'u kenë shpëtuar.</p>\\n<p>Një gjë tjetër e shtuar kohët e fundit është edhe mundësia për të dërguar ftesa (<a title=\\"Invitations\\" href=\\"https://l10n.org.al/user/[simplenews-subscriber:user:uid]/invites\\" target=\\"_blank\\">Invitations</a>), me anë të së cilës mund të ftoni njerëzit e njohur, mjafton që t\'u dini adresën email.</p>\\n<p>Kaq për këtë rradhë. Mbetshi me të mira.</p>\\n<p>Dashamiri</p>\\n<p>&nbsp;</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_simplenews_term\' => array(
        \'en\' => array(
          array(
            \'tid\' => \'3\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1349510621\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/node/12\',
        \'title\' => \'Edit profiles and Invitations\',
        \'identifier\' => \'node/12\',
      ),
      \'simplenews\' => (object) array(
          \'nid\' => \'12\',
          \'tid\' => \'3\',
          \'status\' => \'2\',
          \'sent_subscriber_count\' => \'16\',
          \'name\' => \'Njoftime\',
          \'description\' => \'Njoftime të brendëshme për personat e rregjistruar te Përkthimi i Programeve në Shqip.\',
          \'weight\' => \'0\',
        ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'20\',
      \'uid\' => \'1\',
      \'title\' => \'Udhëzuesi i KTurtle\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'86e90938-3d58-b584-f9a3-a243b093f740\',
      \'nid\' => \'20\',
      \'type\' => \'simplenews\',
      \'language\' => \'en\',
      \'created\' => \'1358586548\',
      \'changed\' => \'1358586710\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'785f61cc-9c08-16b4-25da-e96d199b8465\',
      \'revision_timestamp\' => \'1358586710\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<p>Këtë e kam përkthyer para afro një vit e gjysëm. Tani është importuar edhe te l10n.org.al për mbledhur ndonjë sugjerim (feedback):&nbsp;<a href="https://l10n.org.al/translations/search?lng=sq&amp;project=doc_kdeedu_kturtle">https://l10n.org.al/translations/search?lng=sq&amp;project=doc_kdeedu_kturtle</a>&nbsp;.</p><p>Kurse hartimi (kompilimi) në PDF i udhëzuesit mund të shkarkohet prej këtu:&nbsp;<a href="https://btranslator.org/downloads/kturtle.pdf">https://btranslator.org/downloads/kturtle.pdf</a>&nbsp;ose këtu:&nbsp;<a href="http://www.slideshare.net/dashohoxha/udhzuesi-i-kturtle">http://www.slideshare.net/dashohoxha/udhzuesi-i-kturtle</a></p><p>&nbsp;</p>\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p>Këtë e kam përkthyer para afro një vit e gjysëm. Tani është importuar edhe te l10n.org.al për mbledhur ndonjë sugjerim (feedback):&nbsp;<a href=\\"https://l10n.org.al/translations/search?lng=sq&amp;project=doc_kdeedu_kturtle\\">https://l10n.org.al/translations/search?lng=sq&amp;project=doc_kdeedu_kturtle</a>&nbsp;.</p>\\n<p>Kurse hartimi (kompilimi) në PDF i udhëzuesit mund të shkarkohet prej këtu:&nbsp;<a href=\\"https://btranslator.org/downloads/kturtle.pdf\\">https://btranslator.org/downloads/kturtle.pdf</a>&nbsp;ose këtu:&nbsp;<a href=\\"http://www.slideshare.net/dashohoxha/udhzuesi-i-kturtle\\">http://www.slideshare.net/dashohoxha/udhzuesi-i-kturtle</a></p>\\n<p>&nbsp;</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_simplenews_term\' => array(
        \'en\' => array(
          array(
            \'tid\' => \'3\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1358586548\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/node/20\',
        \'title\' => \'Udhëzuesi i KTurtle\',
        \'identifier\' => \'node/20\',
      ),
      \'simplenews\' => (object) array(
          \'nid\' => \'20\',
          \'tid\' => \'3\',
          \'status\' => \'2\',
          \'sent_subscriber_count\' => \'32\',
          \'name\' => \'Njoftime\',
          \'description\' => \'Njoftime të brendëshme për personat e rregjistruar te Përkthimi i Programeve në Shqip.\',
          \'weight\' => \'0\',
        ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'3\',
      \'uid\' => \'1\',
      \'title\' => \'Privacy Policy\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'5d82f7ac-dd89-2764-ad20-739e4d2396cc\',
      \'nid\' => \'3\',
      \'type\' => \'page\',
      \'language\' => \'en\',
      \'created\' => \'1342858159\',
      \'changed\' => \'1342858159\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'a12cc2b7-32f7-f414-79f2-d1a056e1ce32\',
      \'revision_timestamp\' => \'1342858159\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'The user data provided to this application (for example email address) will be kept confident and will be used only for the purposes of the application.\',
            \'summary\' => \'\',
            \'format\' => \'filtered_html\',
            \'safe_value\' => "<p>The user data provided to this application (for example email address) will be kept confident and will be used only for the purposes of the application.</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1342858159\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/privacy\',
        \'title\' => \'Privacy Policy\',
        \'identifier\' => \'node/3\',
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => array(
        \'pid\' => \'3\',
        \'source\' => \'node/3\',
        \'alias\' => \'privacy\',
        \'language\' => \'en\',
      ),
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'18\',
      \'uid\' => \'1\',
      \'title\' => \'Ndryshimi i emrit të përdoruesit\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'74642868-80e0-8364-c948-7d1a635abbf1\',
      \'nid\' => \'18\',
      \'type\' => \'simplenews\',
      \'language\' => \'en\',
      \'created\' => \'1355110653\',
      \'changed\' => \'1355320874\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'a897c2de-1684-f544-09a9-9ae1b2c02b71\',
      \'revision_timestamp\' => \'1355320874\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<p>Pas disa provave me konfigurimet e Drupal-it, vure re se të jep mundësinë që vetë përdoruesi ta ndryshojë emrit e tij (nëse e ka shënuar gabim gjatë rregjistrimit), p.sh. nga <strong>d_hoxha</strong> mund të bëhet <strong>Dashamir Hoxha</strong>. Shpresoj se kjo lirshmëri që u jepet përdoruesve do përdoret për mirë dhe nuk do abuzohet.</p><p>Tani është e mundur gjithashtu që një përdorues ta mbyllë llogarinë e vetë. E çuditshme, por deri tani kisha harruar ta konfiguroja një gjë të tillë. Pas disa kërkësave për largim nga përdorues të mërzitur nga email-at e përditshëm, e vura re këtë gjë dhe e rregullova. Për ta mbyllur llogarinë mjafton të shkosh te Edit Account, dhe në fund është një buton që thotë Cancel Account. Nëse ka njerëz të tjerë që janë mërzitur nga mesazhet e përditshme, tani është e mundur të largohen. Unë i falenderoj për pjesëmarrjen e deritanishme, dhe shpresoj që në të ardhmen sistemi të funksionojë më mirë, të jetë më i përdorshëm dhe &nbsp;më interesant, dhe ata të kthehen sërish për të kontribuar lidhur me përkthimet.</p>\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p>Pas disa provave me konfigurimet e Drupal-it, vure re se të jep mundësinë që vetë përdoruesi ta ndryshojë emrit e tij (nëse e ka shënuar gabim gjatë rregjistrimit), p.sh. nga <strong>d_hoxha</strong> mund të bëhet <strong>Dashamir Hoxha</strong>. Shpresoj se kjo lirshmëri që u jepet përdoruesve do përdoret për mirë dhe nuk do abuzohet.</p>\\n<p>Tani është e mundur gjithashtu që një përdorues ta mbyllë llogarinë e vetë. E çuditshme, por deri tani kisha harruar ta konfiguroja një gjë të tillë. Pas disa kërkësave për largim nga përdorues të mërzitur nga email-at e përditshëm, e vura re këtë gjë dhe e rregullova. Për ta mbyllur llogarinë mjafton të shkosh te Edit Account, dhe në fund është një buton që thotë Cancel Account. Nëse ka njerëz të tjerë që janë mërzitur nga mesazhet e përditshme, tani është e mundur të largohen. Unë i falenderoj për pjesëmarrjen e deritanishme, dhe shpresoj që në të ardhmen sistemi të funksionojë më mirë, të jetë më i përdorshëm dhe &nbsp;më interesant, dhe ata të kthehen sërish për të kontribuar lidhur me përkthimet.</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'field_simplenews_term\' => array(
        \'en\' => array(
          array(
            \'tid\' => \'3\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1355110653\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/node/18\',
        \'title\' => \'Ndryshimi i emrit të përdoruesit\',
        \'identifier\' => \'node/18\',
      ),
      \'simplenews\' => (object) array(
          \'nid\' => \'18\',
          \'tid\' => \'3\',
          \'status\' => \'2\',
          \'sent_subscriber_count\' => \'30\',
          \'name\' => \'Njoftime\',
          \'description\' => \'Njoftime të brendëshme për personat e rregjistruar te Përkthimi i Programeve në Shqip.\',
          \'weight\' => \'0\',
        ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'9\',
      \'uid\' => \'1\',
      \'title\' => \'Updating Drupal with Drush\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'2\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'8ffd6422-c873-0ac4-0521-9c3294add693\',
      \'nid\' => \'9\',
      \'type\' => \'blog\',
      \'language\' => \'en\',
      \'created\' => \'1342860741\',
      \'changed\' => \'1342860741\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'aa65a378-deac-53e4-7173-602d641a0b79\',
      \'revision_timestamp\' => \'1342860741\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "First, backup the sites. Then give the following commands:\\r\\n\\r\\ndrush -l site1.com vset --yes maintenance_mode 0\\r\\ndrush -l site2.com vset --yes maintenance_mode 0\\r\\ndrush -l site1.com cache-clear all\\r\\ndrush -l site2.com cache-clear all\\r\\ndrush up\\r\\ndrush -l site1.com updb\\r\\ndrush -l site1.com up\\r\\ndrush -l site1.com vset --yes maintenance_mode 1\\r\\ndrush -l site2.com updb\\r\\ndrush -l site2.com up\\r\\ndrush -l site2.com vset --yes maintenance_mode 1\\r\\n\\r\\nFinally restore the sites again.\\r\\n\\r\\n------------------\\r\\n\\r\\nI take a very lazy approach that is quite foolproof. Instead of making a patch I go the route of finding all changed files and replacing them, not replacing any files that were untouched. It leaves the /sites folder undisturbed among other things too.\\r\\n\\r\\n1. Navigate to Drupal root\\r\\n2. wget drupal-x.xx.tar.gz\\r\\n3. tar -xzvf drupal-x.xx.tar.gz\\r\\n4. cd drupal-x.xx\\r\\n5. \\\\cp -Rvupf * ../\\r\\n\\r\\nThe cp command with those flags does all that was said above. Flawless core upgrade every time.\\r\\n\\r\\n--------------------\\r\\n\\r\\nReferences:\\r\\nhttp://cafuego.net/2011/05/27/how-do-you-update-drupal\\r\\n",
            \'summary\' => "First, backup the sites. Then give the following commands:\\r\\n\\r\\ndrush -l site1.com vset --yes maintenance_mode 0\\r\\ndrush -l site2.com vset --yes maintenance_mode 0\\r\\ndrush -l site1.com cache-clear all\\r\\ndrush -l site2.com cache-clear all\\r\\ndrush up\\r\\ndrush -l site1.com updb\\r\\ndrush -l site1.com up\\r\\ndrush -l site1.com vset --yes maintenance_mode 1\\r\\ndrush -l site2.com updb\\r\\ndrush -l site2.com up\\r\\ndrush -l site2.com vset --yes maintenance_mode 1\\r\\n\\r\\nFinally restore the sites again.\\r\\n\\r\\n------------------\\r\\n\\r\\nI take a very lazy approach that is quite foolproof. Instead of making a patch I go the route of finding all changed files and replacing them, not replacing any files that were untouched. It leaves the /sites folder undisturbed among other things too.\\r\\n\\r\\n1. Navigate to Drupal root\\r\\n2. wget drupal-x.xx.tar.gz\\r\\n3. tar -xzvf drupal-x.xx.tar.gz\\r\\n4. cd drupal-x.xx\\r\\n5. \\\\cp -Rvupf * ../\\r\\n\\r\\nThe cp command with those flags does all that was said above. Flawless core upgrade every time.\\r\\n\\r\\n--------------------\\r\\n\\r\\nReferences:\\r\\nhttp://cafuego.net/2011/05/27/how-do-you-update-drupal\\r\\n",
            \'format\' => \'plain_text\',
            \'safe_value\' => "<p>First, backup the sites. Then give the following commands:</p>\\n<p>drush -l site1.com vset --yes maintenance_mode 0<br />\\ndrush -l site2.com vset --yes maintenance_mode 0<br />\\ndrush -l site1.com cache-clear all<br />\\ndrush -l site2.com cache-clear all<br />\\ndrush up<br />\\ndrush -l site1.com updb<br />\\ndrush -l site1.com up<br />\\ndrush -l site1.com vset --yes maintenance_mode 1<br />\\ndrush -l site2.com updb<br />\\ndrush -l site2.com up<br />\\ndrush -l site2.com vset --yes maintenance_mode 1</p>\\n<p>Finally restore the sites again.</p>\\n<p>------------------</p>\\n<p>I take a very lazy approach that is quite foolproof. Instead of making a patch I go the route of finding all changed files and replacing them, not replacing any files that were untouched. It leaves the /sites folder undisturbed among other things too.</p>\\n<p>1. Navigate to Drupal root<br />\\n2. wget drupal-x.xx.tar.gz<br />\\n3. tar -xzvf drupal-x.xx.tar.gz<br />\\n4. cd drupal-x.xx<br />\\n5. \\\\cp -Rvupf * ../</p>\\n<p>The cp command with those flags does all that was said above. Flawless core upgrade every time.</p>\\n<p>--------------------</p>\\n<p>References:<br />\\n<a href=\\"http://cafuego.net/2011/05/27/how-do-you-update-drupal\\">http://cafuego.net/2011/05/27/how-do-you-update-drupal</a></p>\\n",
            \'safe_summary\' => "<p>First, backup the sites. Then give the following commands:</p>\\n<p>drush -l site1.com vset --yes maintenance_mode 0<br />\\ndrush -l site2.com vset --yes maintenance_mode 0<br />\\ndrush -l site1.com cache-clear all<br />\\ndrush -l site2.com cache-clear all<br />\\ndrush up<br />\\ndrush -l site1.com updb<br />\\ndrush -l site1.com up<br />\\ndrush -l site1.com vset --yes maintenance_mode 1<br />\\ndrush -l site2.com updb<br />\\ndrush -l site2.com up<br />\\ndrush -l site2.com vset --yes maintenance_mode 1</p>\\n<p>Finally restore the sites again.</p>\\n<p>------------------</p>\\n<p>I take a very lazy approach that is quite foolproof. Instead of making a patch I go the route of finding all changed files and replacing them, not replacing any files that were untouched. It leaves the /sites folder undisturbed among other things too.</p>\\n<p>1. Navigate to Drupal root<br />\\n2. wget drupal-x.xx.tar.gz<br />\\n3. tar -xzvf drupal-x.xx.tar.gz<br />\\n4. cd drupal-x.xx<br />\\n5. \\\\cp -Rvupf * ../</p>\\n<p>The cp command with those flags does all that was said above. Flawless core upgrade every time.</p>\\n<p>--------------------</p>\\n<p>References:<br />\\n<a href=\\"http://cafuego.net/2011/05/27/how-do-you-update-drupal\\">http://cafuego.net/2011/05/27/how-do-you-update-drupal</a></p>\\n",
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Post\',
          \'sioct:BlogPost\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1342860741\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/node/9\',
        \'title\' => \'Updating Drupal with Drush\',
        \'identifier\' => \'node/9\',
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'6\',
      \'uid\' => \'1\',
      \'title\' => \'Instalimi i Fjalorit Drejtshkrimor\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'2\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'c31f9eef-44f7-1604-a1bb-6762fba0c7f9\',
      \'nid\' => \'6\',
      \'type\' => \'book\',
      \'language\' => \'en\',
      \'created\' => \'1342859673\',
      \'changed\' => \'1342859673\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'be96c8e6-928c-0974-b1a0-e3f0a1324ca5\',
      \'revision_timestamp\' => \'1342859673\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "<p><a href=\\"http://www.shkenca.org/k6i/albanian_dictionary_for_aspell_sq.html\\">Fjalori i gjuhës shqipe për programin Aspell</a> (i cili përdoret për kontroll drejtshkrimor) përmban rreth 550.000 fjalë dhe trajta fjalësh. Instalimi bëhet me hapat e mëposhtëm:</p><ol><li>Shkarkojeni fjalorin nga: <a href=\\"http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2\\">http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2</a><br /><strong>wget http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2</strong></li><li>Shpaketojeni skedarin e porsashkarkuar:<br /><strong>tar -xvjf aspell6-sq-1.6.4-0.tar.bz2</strong></li><li>Kaloni te direktoria <strong>aspell6-sq-1.6.4-0</strong>:<br /><strong>cd aspell6-sq-1.6.4-0</strong></li><li>Instalimi i fjalorit bëhet me komandat:<br /><strong>./configure<br />make<br />sudo make install</strong></li></ol><p><strong>​</strong>Mund të instaloni gjithashtu edhe këtë add-on për Firefox dhe Thunderbird:&nbsp;<a href=\\"https://addons.mozilla.org/en-US/thunderbird/addon/albanian-dictionary/\\">https://addons.mozilla.org/en-US/thunderbird/addon/albanian-dictionary/</a></p><p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p><p>\\r\\n<meta content=\\"text/html; charset=utf-8\\" http-equiv=\\"content-type\\" />\\r\\n</p>",
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p><a href=\\"http://www.shkenca.org/k6i/albanian_dictionary_for_aspell_sq.html\\">Fjalori i gjuhës shqipe për programin Aspell</a> (i cili përdoret për kontroll drejtshkrimor) përmban rreth 550.000 fjalë dhe trajta fjalësh. Instalimi bëhet me hapat e mëposhtëm:</p>\\n<ol>\\n<li>Shkarkojeni fjalorin nga: <a href=\\"http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2\\">http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2</a><br /><strong>wget <a href=\\"http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2\\">http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2</a></strong></li>\\n<li>Shpaketojeni skedarin e porsashkarkuar:<br /><strong>tar -xvjf aspell6-sq-1.6.4-0.tar.bz2</strong></li>\\n<li>Kaloni te direktoria <strong>aspell6-sq-1.6.4-0</strong>:<br /><strong>cd aspell6-sq-1.6.4-0</strong></li>\\n<li>Instalimi i fjalorit bëhet me komandat:<br /><strong>./configure<br />make<br />sudo make install</strong></li>\\n</ol>\\n<p><strong>​</strong>Mund të instaloni gjithashtu edhe këtë add-on për Firefox dhe Thunderbird:&nbsp;<a href=\\"https://addons.mozilla.org/en-US/thunderbird/addon/albanian-dictionary/\\">https://addons.mozilla.org/en-US/thunderbird/addon/albanian-dictionary/</a></p>\\n<p>&nbsp;</p>\\n<p>&nbsp;</p>\\n<p>&nbsp;</p>\\n<p>&nbsp;</p>\\n<p>&nbsp;</p>\\n<p>&nbsp;</p>\\n<p>\\n<meta content=\\"text/html; charset=utf-8\\" http-equiv=\\"content-type\\" />\\n</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'book\' => array(
        \'mlid\' => \'413\',
        \'nid\' => \'6\',
        \'bid\' => \'4\',
        \'menu_name\' => \'book-toc-4\',
        \'plid\' => \'410\',
        \'link_path\' => \'node/6\',
        \'router_path\' => \'node/%\',
        \'link_title\' => \'Instalimi i Fjalorit Drejtshkrimor\',
        \'options\' => array(),
        \'module\' => \'book\',
        \'hidden\' => \'0\',
        \'external\' => \'0\',
        \'has_children\' => \'0\',
        \'expanded\' => \'0\',
        \'weight\' => \'-13\',
        \'depth\' => \'2\',
        \'customized\' => \'0\',
        \'p1\' => \'410\',
        \'p2\' => \'413\',
        \'p3\' => \'0\',
        \'p4\' => \'0\',
        \'p5\' => \'0\',
        \'p6\' => \'0\',
        \'p7\' => \'0\',
        \'p8\' => \'0\',
        \'p9\' => \'0\',
        \'updated\' => \'0\',
        \'href\' => \'node/6\',
        \'title\' => \'Instalimi i Fjalorit Drejtshkrimor\',
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1342859673\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/fjalori-drejtshkrimor\',
        \'title\' => \'Instalimi i Fjalorit Drejtshkrimor\',
        \'identifier\' => \'node/6\',
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => array(
        \'pid\' => \'6\',
        \'source\' => \'node/6\',
        \'alias\' => \'fjalori-drejtshkrimor\',
        \'language\' => \'en\',
      ),
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'5\',
      \'uid\' => \'1\',
      \'title\' => \'Si të Përkthejmë Programet në Ubuntu\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'2\',
      \'promote\' => \'1\',
      \'sticky\' => \'1\',
      \'vuuid\' => \'41b8e950-6bf2-2904-6197-30c54ee046e9\',
      \'nid\' => \'5\',
      \'type\' => \'book\',
      \'language\' => \'en\',
      \'created\' => \'1342858760\',
      \'changed\' => \'1358642546\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'c9ee0cf3-41bd-4404-e927-5bca89374f10\',
      \'revision_timestamp\' => \'1358642546\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<p><span style="font-family: arial, helvetica, sans-serif;">Kjo faqe ka disa udhëzime bazë si mund të fillohet puna për përkthimin e programeve në Ubuntu.</span></p><ol><li><span style="font-family: arial, helvetica, sans-serif;">Fillimisht duhet instaluar gjuha shqipe (shiko: <a href="https://l10n.org.al/ubuntu-shqip">https://l10n.org.al/ubuntu-shqip</a>).</span></li><li><span style="font-family: arial, helvetica, sans-serif;">Duhet instaluar edhe tastiera shqipe, për ti nxjerrë kollaj shkronjat <strong>ë</strong>, <strong>ç</strong>, etj. (shiko:&nbsp;<a href="https://l10n.org.al/tastiera-shqip">https://l10n.org.al/tastiera-shqip</a>).</span></li><li><span style="font-family: arial, helvetica, sans-serif;">Pastaj duhet instaluar programi i përkthimit, Lokalize (me komandën:&nbsp;<strong>sudo apt-get install lokalize</strong>&nbsp;)</span></li><li><span style="font-family: arial, helvetica, sans-serif;">Sigurohu që programi që do përkthehet të jetë i instaluar, p.sh. nqs do përkthehet <em>kubrick</em>, jep komandën: <strong>sudo apt-get install kubrick</strong></span></li><li><span style="font-family: arial, helvetica, sans-serif;">Shkarko skedarin me tekstet e përkthyeshme <strong>kubrick.po</strong> (për të gjetur këtë skedar, më kontakto mua që të të ndihmoj)</span></li><li><span style="font-family: arial, helvetica, sans-serif;">Fillo përkthimin e skedarit <strong>kubrick.po</strong> me ndihmën e programit <em>Lokalize</em>.</span></li><li><span style="font-family: arial, helvetica, sans-serif;">Për të parë se si duket përkthimi, mund të përdorësh këto komanda:Kur ta kesh mbaruar përkthimin (ose kur të jesh lodhur apo mërzitur dhe do që ta lësh), ma dërgo mua skedarin <strong>kubrick.po</strong>, aq sa të kesh përkthyer, që ta çoj te serverat e ubuntu-së.</span><ul><li><strong>msgfmt -o kubrick.mo kubrick.po</strong></li><li><strong>sudo cp kubrick.mo /usr/share/locale-langpack/sq/LC_MESSAGES/</strong></li><li>Pastaj hape programin <em>kubrik</em> dhe ndrysho gjuhën (te <em>Hdihmë &gt; Ndrysho Gjuhën...</em>).</li></ul></li></ol><p><span style="font-family: arial, helvetica, sans-serif;">Mirë është që të instalohet edhe Fjalori Drejtshkrimor (shiko:&nbsp;<a href="https://l10n.org.al/fjalori-drejtshkrimor">https://l10n.org.al/fjalori-drejtshkrimor</a>) i cili ndihmon për të korrigjuar gabimet e shkrimit.</span></p><p><span style="font-family: arial, helvetica, sans-serif;">Po qe se të del ndonjë problem ose vështirësi mund të më kontaktosh për ndihmë (ose shkruaj një koment në fund të kësaj faqes).</span></p>\',
            \'summary\' => \'Kjo faqe ka disa udhëzime bazë si mund të fillohet puna për përkthimin e programeve në Ubuntu. Fillimisht duhet instaluar gjuha shqipe.\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Kjo faqe ka disa udhëzime bazë si mund të fillohet puna për përkthimin e programeve në Ubuntu.</span></p>\\n<ol>\\n<li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Fillimisht duhet instaluar gjuha shqipe (shiko: <a href=\\"https://l10n.org.al/ubuntu-shqip\\">https://l10n.org.al/ubuntu-shqip</a>).</span></li>\\n<li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Duhet instaluar edhe tastiera shqipe, për ti nxjerrë kollaj shkronjat <strong>ë</strong>, <strong>ç</strong>, etj. (shiko:&nbsp;<a href=\\"https://l10n.org.al/tastiera-shqip\\">https://l10n.org.al/tastiera-shqip</a>).</span></li>\\n<li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Pastaj duhet instaluar programi i përkthimit, Lokalize (me komandën:&nbsp;<strong>sudo apt-get install lokalize</strong>&nbsp;)</span></li>\\n<li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Sigurohu që programi që do përkthehet të jetë i instaluar, p.sh. nqs do përkthehet <em>kubrick</em>, jep komandën: <strong>sudo apt-get install kubrick</strong></span></li>\\n<li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Shkarko skedarin me tekstet e përkthyeshme <strong>kubrick.po</strong> (për të gjetur këtë skedar, më kontakto mua që të të ndihmoj)</span></li>\\n<li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Fillo përkthimin e skedarit <strong>kubrick.po</strong> me ndihmën e programit <em>Lokalize</em>.</span></li>\\n<li><span style=\\"font-family: arial, helvetica, sans-serif;\\">Për të parë se si duket përkthimi, mund të përdorësh këto komanda:Kur ta kesh mbaruar përkthimin (ose kur të jesh lodhur apo mërzitur dhe do që ta lësh), ma dërgo mua skedarin <strong>kubrick.po</strong>, aq sa të kesh përkthyer, që ta çoj te serverat e ubuntu-së.</span>\\n<ul>\\n<li><strong>msgfmt -o kubrick.mo kubrick.po</strong></li>\\n<li><strong>sudo cp kubrick.mo /usr/share/locale-langpack/sq/LC_MESSAGES/</strong></li>\\n<li>Pastaj hape programin <em>kubrik</em> dhe ndrysho gjuhën (te <em>Hdihmë &gt; Ndrysho Gjuhën...</em>).</li>\\n</ul>\\n</li>\\n</ol>\\n<p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Mirë është që të instalohet edhe Fjalori Drejtshkrimor (shiko:&nbsp;<a href=\\"https://l10n.org.al/fjalori-drejtshkrimor\\">https://l10n.org.al/fjalori-drejtshkrimor</a>) i cili ndihmon për të korrigjuar gabimet e shkrimit.</span></p>\\n<p><span style=\\"font-family: arial, helvetica, sans-serif;\\">Po qe se të del ndonjë problem ose vështirësi mund të më kontaktosh për ndihmë (ose shkruaj një koment në fund të kësaj faqes).</span></p>\\n",
            \'safe_summary\' => "<p>Kjo faqe ka disa udhëzime bazë si mund të fillohet puna për përkthimin e programeve në Ubuntu. Fillimisht duhet instaluar gjuha shqipe.</p>\\n",
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'book\' => array(
        \'mlid\' => \'412\',
        \'nid\' => \'5\',
        \'bid\' => \'4\',
        \'menu_name\' => \'book-toc-4\',
        \'plid\' => \'410\',
        \'link_path\' => \'node/5\',
        \'router_path\' => \'node/%\',
        \'link_title\' => \'Si të Përkthejmë Programet në Ubuntu\',
        \'options\' => array(),
        \'module\' => \'book\',
        \'hidden\' => \'0\',
        \'external\' => \'0\',
        \'has_children\' => \'0\',
        \'expanded\' => \'0\',
        \'weight\' => \'-12\',
        \'depth\' => \'2\',
        \'customized\' => \'0\',
        \'p1\' => \'410\',
        \'p2\' => \'412\',
        \'p3\' => \'0\',
        \'p4\' => \'0\',
        \'p5\' => \'0\',
        \'p6\' => \'0\',
        \'p7\' => \'0\',
        \'p8\' => \'0\',
        \'p9\' => \'0\',
        \'updated\' => \'0\',
        \'href\' => \'node/5\',
        \'title\' => \'Si të Përkthejmë Programet në Ubuntu\',
      ),
      \'cid\' => \'1\',
      \'last_comment_timestamp\' => \'1342862430\',
      \'last_comment_name\' => \'\',
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'1\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/si-te-perkthejme-programet-ne-ubuntu\',
        \'title\' => \'Si të Përkthejmë Programet në Ubuntu\',
        \'identifier\' => \'node/5\',
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => array(
        \'pid\' => \'5\',
        \'source\' => \'node/5\',
        \'alias\' => \'si-te-perkthejme-programet-ne-ubuntu\',
        \'language\' => \'en\',
      ),
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'7\',
      \'uid\' => \'1\',
      \'title\' => \'Vendosja e Tastierës Shqipe në Ubuntu\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'2\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'1eff3f00-3bfb-a5d4-4d3d-486e55737646\',
      \'nid\' => \'7\',
      \'type\' => \'book\',
      \'language\' => \'en\',
      \'created\' => \'1342859951\',
      \'changed\' => \'1350382378\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'ef4c3957-e41f-b494-6d7a-82fd0b4de407\',
      \'revision_timestamp\' => \'1350382378\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<div style="color: #4d4d4d; font-family: Times, serif; font-size: 16px;">Vendosja e tastierës shqipe në Ubuntu bëhet te&nbsp;<strong>Parametrat e Sistemit</strong>, te&nbsp;<strong>Dalja e Tastierës</strong>&nbsp;(<strong>Keyboard Layout</strong>). Aty klikohet butoni&nbsp;<strong>[+]</strong>&nbsp;(plus), dhe gjendet tastiera&nbsp;<strong>Shqip:</strong></div><div class="separator" style="color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;"><a style="color: #a30200; margin-left: 1em; margin-right: 1em;" href="http://1.bp.blogspot.com/-_csk4dHFd40/UH0ooSCC2oI/AAAAAAAAAyM/oG-6xepLq_A/s1600/planimetria_e_tastieres_shqipe.png"><img style="border-style: none; position: relative;" src="http://1.bp.blogspot.com/-_csk4dHFd40/UH0ooSCC2oI/AAAAAAAAAyM/oG-6xepLq_A/s1600/planimetria_e_tastieres_shqipe.png" alt="" width="640" height="508" border="0"></a></div><div style="color: #4d4d4d; font-family: Times, serif; font-size: 16px;">&nbsp;</div><div style="color: #4d4d4d; font-family: Times, serif; font-size: 16px;">&nbsp;</div><div style="color: #4d4d4d; font-family: Times, serif; font-size: 16px;">Pasi të jetë instaluar tastiera shqip, në shiritin sipër do të dalë edhe një ikonë që shërben për ndërimin e tastierës:<span style="font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; text-align: center;">&nbsp;</span></div><div class="separator" style="color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;"><a style="color: #a30200; margin-left: 1em; margin-right: 1em;" href="http://4.bp.blogspot.com/-euwWKEJS6is/UH0yfJZgkmI/AAAAAAAAAzE/whPZoOprzZA/s1600/zgjidh_planimetrine_shqip_1.png"><img style="border-style: none; position: relative;" src="http://4.bp.blogspot.com/-euwWKEJS6is/UH0yfJZgkmI/AAAAAAAAAzE/whPZoOprzZA/s1600/zgjidh_planimetrine_shqip_1.png" alt="" width="640" height="392" border="0"></a></div><div style="color: #4d4d4d; font-family: Times, serif; font-size: 16px;">&nbsp;</div><div style="color: #4d4d4d; font-family: Times, serif; font-size: 16px;">&nbsp;</div><div style="color: #4d4d4d; font-family: Times, serif; font-size: 16px;">Po aty gjendet edhe menuja&nbsp;<strong>Show Layout Chart</strong>&nbsp;e cila na tregon planimetrinë e tastierës:</div><div class="separator" style="color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;"><a style="text-decoration: underline; color: #db3012; margin-left: 1em; margin-right: 1em;" href="http://2.bp.blogspot.com/-5Cf4o_71ce0/UH0opXFzTkI/AAAAAAAAAyQ/aRDRIc0vyYY/s1600/planimetria_shqipe.png"><img style="border-style: none; position: relative;" src="http://2.bp.blogspot.com/-5Cf4o_71ce0/UH0opXFzTkI/AAAAAAAAAyQ/aRDRIc0vyYY/s1600/planimetria_shqipe.png" alt="" width="640" height="218" border="0"></a></div><p>&nbsp;</p>\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<div style=\\"color: #4d4d4d; font-family: Times, serif; font-size: 16px;\\">Vendosja e tastierës shqipe në Ubuntu bëhet te&nbsp;<strong>Parametrat e Sistemit</strong>, te&nbsp;<strong>Dalja e Tastierës</strong>&nbsp;(<strong>Keyboard Layout</strong>). Aty klikohet butoni&nbsp;<strong>[+]</strong>&nbsp;(plus), dhe gjendet tastiera&nbsp;<strong>Shqip:</strong></div>\\n<div class=\\"separator\\" style=\\"color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;\\"><a style=\\"color: #a30200; margin-left: 1em; margin-right: 1em;\\" href=\\"http://1.bp.blogspot.com/-_csk4dHFd40/UH0ooSCC2oI/AAAAAAAAAyM/oG-6xepLq_A/s1600/planimetria_e_tastieres_shqipe.png\\"><img style=\\"border-style: none; position: relative;\\" src=\\"http://1.bp.blogspot.com/-_csk4dHFd40/UH0ooSCC2oI/AAAAAAAAAyM/oG-6xepLq_A/s1600/planimetria_e_tastieres_shqipe.png\\" alt=\\"\\" width=\\"640\\" height=\\"508\\" border=\\"0\\"></a></div>\\n<div style=\\"color: #4d4d4d; font-family: Times, serif; font-size: 16px;\\">&nbsp;</div>\\n<div style=\\"color: #4d4d4d; font-family: Times, serif; font-size: 16px;\\">&nbsp;</div>\\n<div style=\\"color: #4d4d4d; font-family: Times, serif; font-size: 16px;\\">Pasi të jetë instaluar tastiera shqip, në shiritin sipër do të dalë edhe një ikonë që shërben për ndërimin e tastierës:<span style=\\"font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; text-align: center;\\">&nbsp;</span></div>\\n<div class=\\"separator\\" style=\\"color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;\\"><a style=\\"color: #a30200; margin-left: 1em; margin-right: 1em;\\" href=\\"http://4.bp.blogspot.com/-euwWKEJS6is/UH0yfJZgkmI/AAAAAAAAAzE/whPZoOprzZA/s1600/zgjidh_planimetrine_shqip_1.png\\"><img style=\\"border-style: none; position: relative;\\" src=\\"http://4.bp.blogspot.com/-euwWKEJS6is/UH0yfJZgkmI/AAAAAAAAAzE/whPZoOprzZA/s1600/zgjidh_planimetrine_shqip_1.png\\" alt=\\"\\" width=\\"640\\" height=\\"392\\" border=\\"0\\"></a></div>\\n<div style=\\"color: #4d4d4d; font-family: Times, serif; font-size: 16px;\\">&nbsp;</div>\\n<div style=\\"color: #4d4d4d; font-family: Times, serif; font-size: 16px;\\">&nbsp;</div>\\n<div style=\\"color: #4d4d4d; font-family: Times, serif; font-size: 16px;\\">Po aty gjendet edhe menuja&nbsp;<strong>Show Layout Chart</strong>&nbsp;e cila na tregon planimetrinë e tastierës:</div>\\n<div class=\\"separator\\" style=\\"color: #4d4d4d; font-family: Arial, Tahoma, Helvetica, FreeSans, sans-serif; font-size: 15px; clear: both; text-align: center;\\"><a style=\\"text-decoration: underline; color: #db3012; margin-left: 1em; margin-right: 1em;\\" href=\\"http://2.bp.blogspot.com/-5Cf4o_71ce0/UH0opXFzTkI/AAAAAAAAAyQ/aRDRIc0vyYY/s1600/planimetria_shqipe.png\\"><img style=\\"border-style: none; position: relative;\\" src=\\"http://2.bp.blogspot.com/-5Cf4o_71ce0/UH0opXFzTkI/AAAAAAAAAyQ/aRDRIc0vyYY/s1600/planimetria_shqipe.png\\" alt=\\"\\" width=\\"640\\" height=\\"218\\" border=\\"0\\"></a></div>\\n<p>&nbsp;</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'book\' => array(
        \'mlid\' => \'414\',
        \'nid\' => \'7\',
        \'bid\' => \'4\',
        \'menu_name\' => \'book-toc-4\',
        \'plid\' => \'410\',
        \'link_path\' => \'node/7\',
        \'router_path\' => \'node/%\',
        \'link_title\' => \'Vendosja e Tastierës Shqipe në Ubuntu\',
        \'options\' => array(),
        \'module\' => \'book\',
        \'hidden\' => \'0\',
        \'external\' => \'0\',
        \'has_children\' => \'0\',
        \'expanded\' => \'0\',
        \'weight\' => \'-14\',
        \'depth\' => \'2\',
        \'customized\' => \'0\',
        \'p1\' => \'410\',
        \'p2\' => \'414\',
        \'p3\' => \'0\',
        \'p4\' => \'0\',
        \'p5\' => \'0\',
        \'p6\' => \'0\',
        \'p7\' => \'0\',
        \'p8\' => \'0\',
        \'p9\' => \'0\',
        \'updated\' => \'0\',
        \'href\' => \'node/7\',
        \'title\' => \'Vendosja e Tastierës Shqipe në Ubuntu\',
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1342859951\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/tastiera-shqipe\',
        \'title\' => \'Vendosja e Tastierës Shqipe në Ubuntu\',
        \'identifier\' => \'node/7\',
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => array(
        \'pid\' => \'7\',
        \'source\' => \'node/7\',
        \'alias\' => \'tastiera-shqipe\',
        \'language\' => \'en\',
      ),
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'19\',
      \'uid\' => \'1\',
      \'title\' => \'Exportet e përnatshme automatike\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'2\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'18cdd14d-0a98-1f24-5537-88e066cae6c4\',
      \'nid\' => \'19\',
      \'type\' => \'mass_contact\',
      \'language\' => \'und\',
      \'created\' => \'1356550150\',
      \'changed\' => \'1356560066\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'f0b35fad-6833-07e4-d1c6-9cfd6f48c7d1\',
      \'revision_timestamp\' => \'1356560066\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "<p>Njatjeta,</p>\\r\\n<p>Më duket se kam harruar tju them se sistemi krijon çdo natë<br />\\r\\nautomatikisht ekportet e disa prej projekteve aktive. Këto mund<br />\\r\\ntë shihen dhe të shkarkohen këtu:<br />\\r\\n<a href=\\"https://l10n.org.al/downloads/exports/\\">https://l10n.org.al/downloads/exports/</a></p>\\r\\n<p>Nuk ka kuptim dhe as dobi që të eksportohen të gjitha projektet,<br />\\r\\nkështu që për momentin eksportohen vetëm KDE/all, Mozilla/all,<br />\\r\\ndhe misc/pingus. Nëse mendoni se duhet përfshirë edhe ndonjë<br />\\r\\nprojekt tjetër në këtë listë, më thoni, nuk është e vështirë për<br />\\r\\nta shtuar.</p>\\r\\n<p>Dashamiri</p>\\r\\n",
            \'summary\' => "<p>Njatjeta,</p>\\r\\n<p>Më duket se kam harruar tju them se sistemi krijon çdo natë<br />\\r\\nautomatikisht ekportet e disa prej projekteve aktive. Këto mund<br />\\r\\ntë shihen dhe të shkarkohen këtu:<br />\\r\\n<a href=\\"https://l10n.org.al/downloads/exports/\\">https://l10n.org.al/downloads/exports/</a></p>\\r\\n<p>Nuk ka kuptim dhe as dobi që të eksportohen të gjitha projektet,<br />\\r\\nkështu që për momentin eksportohen vetëm KDE/all, Mozilla/all,<br />\\r\\ndhe misc/pingus. Nëse mendoni se duhet përfshirë edhe ndonjë<br />\\r\\nprojekt tjetër në këtë listë, më thoni, nuk është e vështirë për<br />\\r\\nta shtuar.</p>",
            \'format\' => \'plain_text\',
            \'safe_value\' => "<p>&lt;p&gt;Njatjeta,&lt;/p&gt;<br />\\n&lt;p&gt;Më duket se kam harruar tju them se sistemi krijon çdo natë&lt;br /&gt;<br />\\nautomatikisht ekportet e disa prej projekteve aktive. Këto mund&lt;br /&gt;<br />\\ntë shihen dhe të shkarkohen këtu:&lt;br /&gt;<br />\\n&lt;a href=&quot;<a href=\\"https://l10n.org.al/downloads/exports/&quot;&gt;https://l10n.org.al/downloads/exports/&lt;/a&gt;&lt;/p&gt;\\">https://l10n.org.al/downloads/exports/&quot;&gt;https://l10n.org.al/downloads/ex...</a><br />\\n&lt;p&gt;Nuk ka kuptim dhe as dobi që të eksportohen të gjitha projektet,&lt;br /&gt;<br />\\nkështu që për momentin eksportohen vetëm KDE/all, Mozilla/all,&lt;br /&gt;<br />\\ndhe misc/pingus. Nëse mendoni se duhet përfshirë edhe ndonjë&lt;br /&gt;<br />\\nprojekt tjetër në këtë listë, më thoni, nuk është e vështirë për&lt;br /&gt;<br />\\nta shtuar.&lt;/p&gt;<br />\\n&lt;p&gt;Dashamiri&lt;/p&gt;</p>\\n",
            \'safe_summary\' => "<p>&lt;p&gt;Njatjeta,&lt;/p&gt;<br />\\n&lt;p&gt;Më duket se kam harruar tju them se sistemi krijon çdo natë&lt;br /&gt;<br />\\nautomatikisht ekportet e disa prej projekteve aktive. Këto mund&lt;br /&gt;<br />\\ntë shihen dhe të shkarkohen këtu:&lt;br /&gt;<br />\\n&lt;a href=&quot;<a href=\\"https://l10n.org.al/downloads/exports/&quot;&gt;https://l10n.org.al/downloads/exports/&lt;/a&gt;&lt;/p&gt;\\">https://l10n.org.al/downloads/exports/&quot;&gt;https://l10n.org.al/downloads/ex...</a><br />\\n&lt;p&gt;Nuk ka kuptim dhe as dobi që të eksportohen të gjitha projektet,&lt;br /&gt;<br />\\nkështu që për momentin eksportohen vetëm KDE/all, Mozilla/all,&lt;br /&gt;<br />\\ndhe misc/pingus. Nëse mendoni se duhet përfshirë edhe ndonjë&lt;br /&gt;<br />\\nprojekt tjetër në këtë listë, më thoni, nuk është e vështirë për&lt;br /&gt;<br />\\nta shtuar.&lt;/p&gt;</p>\\n",
          ),
        ),
      ),
      \'field_mass_contact_from\' => array(
        \'und\' => array(
          array(
            \'value\' => \'info@l10n.org.al\',
            \'format\' => NULL,
            \'safe_value\' => \'info@l10n.org.al\',
          ),
        ),
      ),
      \'field_mass_contact_category\' => array(
        \'und\' => array(
          array(
            \'value\' => \'All categories combined\',
            \'format\' => NULL,
            \'safe_value\' => \'All categories combined\',
          ),
        ),
      ),
      \'field_mass_contact_to\' => array(
        \'und\' => array(
          array(
            \'value\' => \'info@l10n.org.al\',
            \'format\' => NULL,
            \'safe_value\' => \'info@l10n.org.al\',
          ),
        ),
      ),
      \'field_mass_contact_bcc\' => array(
        \'und\' => array(
          array(
            \'value\' => \'as9902613@gmail.com\',
            \'format\' => NULL,
            \'safe_value\' => \'as9902613@gmail.com\',
          ),
          array(
            \'value\' => \' dashohoxha@gmail.com\',
            \'format\' => NULL,
            \'safe_value\' => \' dashohoxha@gmail.com\',
          ),
          array(
            \'value\' => \' besnik@programeshqip.org\',
            \'format\' => NULL,
            \'safe_value\' => \' besnik@programeshqip.org\',
          ),
          array(
            \'value\' => \' banago@gmail.com\',
            \'format\' => NULL,
            \'safe_value\' => \' banago@gmail.com\',
          ),
          array(
            \'value\' => \' laurenti@alblinux.net\',
            \'format\' => NULL,
            \'safe_value\' => \' laurenti@alblinux.net\',
          ),
          array(
            \'value\' => \' neki.frasheri@gmail.com\',
            \'format\' => NULL,
            \'safe_value\' => \' neki.frasheri@gmail.com\',
          ),
        ),
      ),
      \'field_mass_contact_headers\' => array(
        \'und\' => array(
          array(
            \'value\' => "Content-Type: text/html; charset=UTF-8\\r\\nBcc: as9902613@gmail.com, dashohoxha@gmail.com, besnik@programeshqip.org, banago@gmail.com, laurenti@alblinux.net, neki.frasheri@gmail.com\\r\\n",
            \'format\' => NULL,
            \'safe_value\' => "Content-Type: text/html; charset=UTF-8\\r\\nBcc: as9902613@gmail.com, dashohoxha@gmail.com, besnik@programeshqip.org, banago@gmail.com, laurenti@alblinux.net, neki.frasheri@gmail.com\\r\\n",
          ),
        ),
      ),
      \'field_mass_contact_result\' => array(
        \'und\' => array(
          array(
            \'value\' => \'1\',
            \'format\' => NULL,
            \'safe_value\' => \'1\',
          ),
        ),
      ),
      \'field_mass_contact_attachments\' => array(),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1356550150\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'http://l10n_sq/node/19\',
        \'title\' => \'Exportet e përnatshme automatike\',
        \'identifier\' => \'node/19\',
      ),
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
)',
);
  return $node_export;
}
