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
      \'vid\' => \'22\',
      \'uid\' => \'0\',
      \'title\' => \'Instalimi i Fjalorit Drejtshkrimor\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'c31f9eef-44f7-1604-a1bb-6762fba0c7f9\',
      \'nid\' => \'22\',
      \'type\' => \'book\',
      \'language\' => \'en\',
      \'created\' => \'1371474911\',
      \'changed\' => \'1371474911\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'04ff4698-bddc-4974-8d02-56a84f83a4e9\',
      \'revision_timestamp\' => \'1371474911\',
      \'revision_uid\' => \'0\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<p><a href="http://www.shkenca.org/k6i/albanian_dictionary_for_aspell_sq.html">Fjalori i gjuhës shqipe për programin Aspell</a> (i cili përdoret për kontroll drejtshkrimor) përmban rreth 550.000 fjalë dhe trajta fjalësh. Instalimi bëhet me hapat e mëposhtëm:</p><ol><li>Shkarkojeni fjalorin nga: <a href="http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2">http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2</a><br><strong>wget http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2</strong></li><li>Shpaketojeni skedarin e porsashkarkuar:<br><strong>tar -xvjf aspell6-sq-1.6.4-0.tar.bz2</strong></li><li>Kaloni te direktoria <strong>aspell6-sq-1.6.4-0</strong>:<br><strong>cd aspell6-sq-1.6.4-0</strong></li><li>Instalimi i fjalorit bëhet me komandat:<br><strong>./configure<br>make<br>sudo make install</strong></li></ol><p><strong>​</strong>Mund të instaloni gjithashtu edhe këtë add-on për Firefox dhe Thunderbird:&nbsp;<a href="https://addons.mozilla.org/en-US/thunderbird/addon/albanian-dictionary/">https://addons.mozilla.org/en-US/thunderbird/addon/albanian-dictionary/</a></p><p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p>\',
            \'summary\' => \'\',
            \'format\' => \'full_html\',
            \'safe_value\' => "<p><a href=\\"http://www.shkenca.org/k6i/albanian_dictionary_for_aspell_sq.html\\">Fjalori i gjuhës shqipe për programin Aspell</a> (i cili përdoret për kontroll drejtshkrimor) përmban rreth 550.000 fjalë dhe trajta fjalësh. Instalimi bëhet me hapat e mëposhtëm:</p>\\n<ol>\\n<li>Shkarkojeni fjalorin nga: <a href=\\"http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2\\">http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2</a><br><strong>wget <a href=\\"http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2\\">http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2</a></strong></li>\\n<li>Shpaketojeni skedarin e porsashkarkuar:<br><strong>tar -xvjf aspell6-sq-1.6.4-0.tar.bz2</strong></li>\\n<li>Kaloni te direktoria <strong>aspell6-sq-1.6.4-0</strong>:<br><strong>cd aspell6-sq-1.6.4-0</strong></li>\\n<li>Instalimi i fjalorit bëhet me komandat:<br><strong>./configure<br>make<br>sudo make install</strong></li>\\n</ol>\\n<p><strong>​</strong>Mund të instaloni gjithashtu edhe këtë add-on për Firefox dhe Thunderbird:&nbsp;<a href=\\"https://addons.mozilla.org/en-US/thunderbird/addon/albanian-dictionary/\\">https://addons.mozilla.org/en-US/thunderbird/addon/albanian-dictionary/</a></p>\\n<p>&nbsp;</p>\\n<p>&nbsp;</p>\\n<p>&nbsp;</p>\\n<p>&nbsp;</p>\\n<p>&nbsp;</p>\\n<p>&nbsp;</p>\\n<p>&nbsp;</p>\\n",
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
        \'mlid\' => \'669\',
        \'nid\' => \'22\',
        \'bid\' => \'39\',
        \'menu_name\' => \'book-toc-39\',
        \'plid\' => \'0\',
        \'link_path\' => \'node/22\',
        \'router_path\' => \'node/%\',
        \'link_title\' => \'Instalimi i Fjalorit Drejtshkrimor\',
        \'options\' => array(),
        \'module\' => \'book\',
        \'hidden\' => \'0\',
        \'external\' => \'0\',
        \'has_children\' => \'0\',
        \'expanded\' => \'0\',
        \'weight\' => \'-13\',
        \'depth\' => \'1\',
        \'customized\' => \'0\',
        \'p1\' => \'669\',
        \'p2\' => \'0\',
        \'p3\' => \'0\',
        \'p4\' => \'0\',
        \'p5\' => \'0\',
        \'p6\' => \'0\',
        \'p7\' => \'0\',
        \'p8\' => \'0\',
        \'p9\' => \'0\',
        \'updated\' => \'0\',
        \'href\' => \'node/22\',
        \'title\' => \'Instalimi i Fjalorit Drejtshkrimor\',
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1371474911\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'0\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'https://dev.l10n.org.al/node/22\',
        \'title\' => \'Instalimi i Fjalorit Drejtshkrimor\',
        \'identifier\' => \'node/22\',
        \'developer\' => 1,
      ),
      \'name\' => \'\',
      \'picture\' => \'0\',
      \'data\' => NULL,
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'23\',
      \'uid\' => \'0\',
      \'title\' => \'Server i ri për l10n.org.al\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'1\',
      \'sticky\' => \'1\',
      \'vuuid\' => \'bbb5e7e8-abd5-c2a4-012a-c02a137cf93c\',
      \'nid\' => \'23\',
      \'type\' => \'blog\',
      \'language\' => \'en\',
      \'created\' => \'1371474911\',
      \'changed\' => \'1371474911\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'1b574c84-6611-4bde-b5d2-e24cd59ec9a6\',
      \'revision_timestamp\' => \'1371474911\',
      \'revision_uid\' => \'0\',
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
      \'last_comment_timestamp\' => \'1371474911\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'0\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'https://dev.l10n.org.al/node/23\',
        \'title\' => \'Server i ri për l10n.org.al\',
        \'identifier\' => \'node/23\',
        \'developer\' => 1,
      ),
      \'name\' => \'\',
      \'picture\' => \'0\',
      \'data\' => NULL,
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'24\',
      \'uid\' => \'0\',
      \'title\' => \'Privacy Policy\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'5d82f7ac-dd89-2764-ad20-739e4d2396cc\',
      \'nid\' => \'24\',
      \'type\' => \'page\',
      \'language\' => \'en\',
      \'created\' => \'1371474911\',
      \'changed\' => \'1371474911\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'22ca1b5b-31d6-4bfb-be6f-c5c679af27d9\',
      \'revision_timestamp\' => \'1371474911\',
      \'revision_uid\' => \'0\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<p>The user data provided to this application (for example email address) will be kept confident and will be used only for the purposes of the application.</p>\',
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
      \'last_comment_timestamp\' => \'1371474911\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'0\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'https://dev.l10n.org.al/node/24\',
        \'title\' => \'Privacy Policy\',
        \'identifier\' => \'node/24\',
        \'developer\' => 1,
      ),
      \'name\' => \'\',
      \'picture\' => \'0\',
      \'data\' => NULL,
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'25\',
      \'uid\' => \'0\',
      \'title\' => \'About\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'e5ac3a68-b17f-feb4-95e6-21b5907f7816\',
      \'nid\' => \'25\',
      \'type\' => \'page\',
      \'language\' => \'en\',
      \'created\' => \'1371474911\',
      \'changed\' => \'1371474911\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'3bb54687-668d-40d7-8683-c7318ac99856\',
      \'revision_timestamp\' => \'1371474911\',
      \'revision_uid\' => \'0\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<p>Kjo faqe ka si qëllim të ndihmojë dhe të koordinojë përkthimin e programeve kompjuterike në gjuhën shqipe. (...së shpejti) <iframe style="border: none; overflow: hidden; width: 450px; height: 450px;" src="http://www.facebook.com/plugins/likebox.php?href=http%3A%2F%2Fwww.facebook.com%2FE.Duam.Kompjuterin.Shqip&amp;width=450&amp;colorscheme=light&amp;show_faces=true&amp;border_color&amp;stream=true&amp;header=false&amp;height=450" frameborder="0" scrolling="no"></iframe></p>\',
            \'summary\' => "Kjo faqe ka si qëllim të ndihmojë dhe të koordinojë përkthimin e programeve kompjuterike në gjuhën shqipe. (...së shpejti)\\r\\n\\r\\n<iframe src=\\"http://www.facebook.com/plugins/likebox.php?href=http%3A%2F%2Fwww.facebook.com%2FE.Duam.Kompjuterin.Shqip&amp;width=450&amp;colorscheme=light&amp;show_faces=true&amp;border_color&amp;stream=true&amp;header=false&amp;height=450\\" scrolling=\\"no\\" frameborder=\\"0\\" style=\\"border:none; overflow:hidden; width:450px; height:450px;\\" allowTransparency=\\"true\\"></iframe>",
            \'format\' => \'full_html\',
            \'safe_value\' => "<p>Kjo faqe ka si qëllim të ndihmojë dhe të koordinojë përkthimin e programeve kompjuterike në gjuhën shqipe. (...së shpejti) </p>\\n<iframe style=\\"border: none; overflow: hidden; width: 450px; height: 450px;\\" src=\\"http://www.facebook.com/plugins/likebox.php?href=http%3A%2F%2Fwww.facebook.com%2FE.Duam.Kompjuterin.Shqip&amp;width=450&amp;colorscheme=light&amp;show_faces=true&amp;border_color&amp;stream=true&amp;header=false&amp;height=450\\" frameborder=\\"0\\" scrolling=\\"no\\"></iframe></p>\\n",
            \'safe_summary\' => "<p>Kjo faqe ka si qëllim të ndihmojë dhe të koordinojë përkthimin e programeve kompjuterike në gjuhën shqipe. (...së shpejti)</p>\\n<iframe src=\\"http://www.facebook.com/plugins/likebox.php?href=http%3A%2F%2Fwww.facebook.com%2FE.Duam.Kompjuterin.Shqip&amp;width=450&amp;colorscheme=light&amp;show_faces=true&amp;border_color&amp;stream=true&amp;header=false&amp;height=450\\" scrolling=\\"no\\" frameborder=\\"0\\" style=\\"border:none; overflow:hidden; width:450px; height:450px;\\" allowTransparency=\\"true\\"></iframe>",
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
      \'last_comment_timestamp\' => \'1371474911\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'0\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'https://dev.l10n.org.al/node/25\',
        \'title\' => \'About\',
        \'identifier\' => \'node/25\',
        \'developer\' => 1,
      ),
      \'name\' => \'\',
      \'picture\' => \'0\',
      \'data\' => NULL,
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'26\',
      \'uid\' => \'0\',
      \'title\' => \'Udhëzuesi i Përkthyesit\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'4338fea8-e287-ec74-39da-2d27df55e8b2\',
      \'nid\' => \'26\',
      \'type\' => \'book\',
      \'language\' => \'en\',
      \'created\' => \'1371474911\',
      \'changed\' => \'1371474911\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'9e1ce491-f48e-425d-a7a1-650b0207451e\',
      \'revision_timestamp\' => \'1371474911\',
      \'revision_uid\' => \'0\',
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
        \'mlid\' => \'670\',
        \'nid\' => \'26\',
        \'bid\' => \'30\',
        \'menu_name\' => \'book-toc-30\',
        \'plid\' => \'0\',
        \'link_path\' => \'node/26\',
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
        \'p1\' => \'670\',
        \'p2\' => \'0\',
        \'p3\' => \'0\',
        \'p4\' => \'0\',
        \'p5\' => \'0\',
        \'p6\' => \'0\',
        \'p7\' => \'0\',
        \'p8\' => \'0\',
        \'p9\' => \'0\',
        \'updated\' => \'0\',
        \'href\' => \'node/26\',
        \'title\' => \'Udhëzuesi i Përkthyesit\',
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1371474911\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'0\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'https://dev.l10n.org.al/node/26\',
        \'title\' => \'Udhëzuesi i Përkthyesit\',
        \'identifier\' => \'node/26\',
        \'developer\' => 1,
      ),
      \'name\' => \'\',
      \'picture\' => \'0\',
      \'data\' => NULL,
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'27\',
      \'uid\' => \'0\',
      \'title\' => \'Vendosja e Gjuhës Shqipe në Ubuntu\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'2cccc4aa-18bf-0ca4-0195-d060316ad28a\',
      \'nid\' => \'27\',
      \'type\' => \'book\',
      \'language\' => \'en\',
      \'created\' => \'1371474911\',
      \'changed\' => \'1371474911\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'bd6727b9-cb89-4e55-8854-0daf971e6dfb\',
      \'revision_timestamp\' => \'1371474911\',
      \'revision_uid\' => \'0\',
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
        \'mlid\' => \'671\',
        \'nid\' => \'27\',
        \'bid\' => \'25\',
        \'menu_name\' => \'book-toc-25\',
        \'plid\' => \'0\',
        \'link_path\' => \'node/27\',
        \'router_path\' => \'node/%\',
        \'link_title\' => \'Vendosja e Gjuhës Shqipe në Ubuntu\',
        \'options\' => array(),
        \'module\' => \'book\',
        \'hidden\' => \'0\',
        \'external\' => \'0\',
        \'has_children\' => \'0\',
        \'expanded\' => \'0\',
        \'weight\' => \'-15\',
        \'depth\' => \'1\',
        \'customized\' => \'0\',
        \'p1\' => \'671\',
        \'p2\' => \'0\',
        \'p3\' => \'0\',
        \'p4\' => \'0\',
        \'p5\' => \'0\',
        \'p6\' => \'0\',
        \'p7\' => \'0\',
        \'p8\' => \'0\',
        \'p9\' => \'0\',
        \'updated\' => \'0\',
        \'href\' => \'node/27\',
        \'title\' => \'Vendosja e Gjuhës Shqipe në Ubuntu\',
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1371474911\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'0\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'https://dev.l10n.org.al/node/27\',
        \'title\' => \'Vendosja e Gjuhës Shqipe në Ubuntu\',
        \'identifier\' => \'node/27\',
        \'developer\' => 1,
      ),
      \'name\' => \'\',
      \'picture\' => \'0\',
      \'data\' => NULL,
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'28\',
      \'uid\' => \'0\',
      \'title\' => \'Terms of Service\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'60df27dc-1b3a-8eb4-5512-ff65210dbf9b\',
      \'nid\' => \'28\',
      \'type\' => \'page\',
      \'language\' => \'en\',
      \'created\' => \'1371474911\',
      \'changed\' => \'1371474911\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'cdd868f4-63bd-4c89-b1cc-87d32fe3358f\',
      \'revision_timestamp\' => \'1371474911\',
      \'revision_uid\' => \'0\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'<p>The services of this application will be used in good faith. Any disputes will be solved with agreement and mutual understanding.</p>\',
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
      \'last_comment_timestamp\' => \'1371474911\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'0\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'https://dev.l10n.org.al/node/28\',
        \'title\' => \'Terms of Service\',
        \'identifier\' => \'node/28\',
        \'developer\' => 1,
      ),
      \'name\' => \'\',
      \'picture\' => \'0\',
      \'data\' => NULL,
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'29\',
      \'uid\' => \'0\',
      \'title\' => \'Si të Përkthejmë Programet në Ubuntu\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'1\',
      \'sticky\' => \'1\',
      \'vuuid\' => \'41b8e950-6bf2-2904-6197-30c54ee046e9\',
      \'nid\' => \'29\',
      \'type\' => \'book\',
      \'language\' => \'en\',
      \'created\' => \'1371474911\',
      \'changed\' => \'1371474911\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'ddf320ff-c253-42cf-8a8e-9dd7c1a39436\',
      \'revision_timestamp\' => \'1371474911\',
      \'revision_uid\' => \'0\',
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
        \'mlid\' => \'672\',
        \'nid\' => \'29\',
        \'bid\' => \'40\',
        \'menu_name\' => \'book-toc-40\',
        \'plid\' => \'0\',
        \'link_path\' => \'node/29\',
        \'router_path\' => \'node/%\',
        \'link_title\' => \'Si të Përkthejmë Programet në Ubuntu\',
        \'options\' => array(),
        \'module\' => \'book\',
        \'hidden\' => \'0\',
        \'external\' => \'0\',
        \'has_children\' => \'0\',
        \'expanded\' => \'0\',
        \'weight\' => \'-12\',
        \'depth\' => \'1\',
        \'customized\' => \'0\',
        \'p1\' => \'672\',
        \'p2\' => \'0\',
        \'p3\' => \'0\',
        \'p4\' => \'0\',
        \'p5\' => \'0\',
        \'p6\' => \'0\',
        \'p7\' => \'0\',
        \'p8\' => \'0\',
        \'p9\' => \'0\',
        \'updated\' => \'0\',
        \'href\' => \'node/29\',
        \'title\' => \'Si të Përkthejmë Programet në Ubuntu\',
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1371474911\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'0\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'https://dev.l10n.org.al/node/29\',
        \'title\' => \'Si të Përkthejmë Programet në Ubuntu\',
        \'identifier\' => \'node/29\',
        \'developer\' => 1,
      ),
      \'name\' => \'\',
      \'picture\' => \'0\',
      \'data\' => NULL,
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'30\',
      \'uid\' => \'0\',
      \'title\' => \'Vendosja e Tastierës Shqipe në Ubuntu\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'1eff3f00-3bfb-a5d4-4d3d-486e55737646\',
      \'nid\' => \'30\',
      \'type\' => \'book\',
      \'language\' => \'en\',
      \'created\' => \'1371474911\',
      \'changed\' => \'1371474911\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'eee12a5b-41d2-4c8d-97e0-c128a2e28522\',
      \'revision_timestamp\' => \'1371474911\',
      \'revision_uid\' => \'0\',
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
        \'mlid\' => \'673\',
        \'nid\' => \'30\',
        \'bid\' => \'41\',
        \'menu_name\' => \'book-toc-41\',
        \'plid\' => \'0\',
        \'link_path\' => \'node/30\',
        \'router_path\' => \'node/%\',
        \'link_title\' => \'Vendosja e Tastierës Shqipe në Ubuntu\',
        \'options\' => array(),
        \'module\' => \'book\',
        \'hidden\' => \'0\',
        \'external\' => \'0\',
        \'has_children\' => \'0\',
        \'expanded\' => \'0\',
        \'weight\' => \'-14\',
        \'depth\' => \'1\',
        \'customized\' => \'0\',
        \'p1\' => \'673\',
        \'p2\' => \'0\',
        \'p3\' => \'0\',
        \'p4\' => \'0\',
        \'p5\' => \'0\',
        \'p6\' => \'0\',
        \'p7\' => \'0\',
        \'p8\' => \'0\',
        \'p9\' => \'0\',
        \'updated\' => \'0\',
        \'href\' => \'node/30\',
        \'title\' => \'Vendosja e Tastierës Shqipe në Ubuntu\',
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1371474911\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'0\',
      \'comment_count\' => \'0\',
      \'disqus\' => array(
        \'domain\' => \'l10n-sq\',
        \'status\' => TRUE,
        \'url\' => \'https://dev.l10n.org.al/node/30\',
        \'title\' => \'Vendosja e Tastierës Shqipe në Ubuntu\',
        \'identifier\' => \'node/30\',
        \'developer\' => 1,
      ),
      \'name\' => \'\',
      \'picture\' => \'0\',
      \'data\' => NULL,
      \'path\' => FALSE,
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
)',
);
  return $node_export;
}
