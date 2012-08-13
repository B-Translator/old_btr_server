<?php
$node = new stdClass();
$node->type = 'book';
node_object_prepare($node);

$node->title    = 'Udhëzuesi i Përkthyesit';
$node->language = LANGUAGE_NONE;
$node->path = array('alias' => 'udhezuesi');
$node->menu = array(
  'enabled' => 1,
  'module' => 'menu',
  //'hidden' => 0,
  'link_title' => 'Udhëzuesi i Përkthyesit',
  'parent' => 'main-menu:0',
  'weight' => 5,
  'menu_name' => 'main-menu',
);
$node = node_submit($node);
node_save($node);

// get the book_id
$book_id = $node->nid;

$node->book['bid'] = $book_id;
node_save($node);

/* ---------------------------- */

$node = new stdClass();
$node->type = 'book';
node_object_prepare($node);

$node->title = 'Si të Përkthejmë Programet në Ubuntu';
$node->path = array('alias' => 'si-te-perkthejme-programet-ne-ubuntu');
$node->book['bid'] = $book_id;
$node->language = LANGUAGE_NONE;
$node->body[LANGUAGE_NONE][0]['format']  = 'full_html';
$node->body[LANGUAGE_NONE][0]['value']   = '
<p>Kjo faqe ka disa udhëzime bazë si mund të fillohet puna për përkthimin e programeve në Ubuntu.</p>
<ol>
  <li>Fillimisht duhet instaluar gjuha shqipe (shiko:
    <a href="https://l10n.org.al/ubuntu-shqip">https://l10n.org.al/ubuntu-shqip</a>).
  </li>
  <li>Duhet instaluar edhe tastiera shqipe, për ti nxjerrë kollaj shkronjat
    <strong>ë</strong>,
    <strong>ç</strong>, etj. (shiko:&nbsp;
    <a href="https://l10n.org.al/tastiera-shqip">https://l10n.org.al/tastiera-shqip</a>).
  </li>
  <li>Pastaj duhet instaluar programi i përkthimit, Lokalize (me komandën:&nbsp;
    <strong>sudo apt-get install lokalize</strong>&nbsp;)
  </li>
  <li>Sigurohu që programi që do përkthehet të jetë i instaluar, p.sh. Nqs do përkthehet
    <em>kubrick</em>, jep komandën:
    <strong>sudo apt-get install kubrick</strong>
  </li>
  <li>Shkarko skedarin me tekstet e përkthyeshme
    <strong>kubrick.po</strong> (për të gjetur këtë skedar, më kontakto mua që të të ndihmoj)
  </li>
  <li>Fillo përkthimin e skedarit
    <strong>kubrick.po</strong> me ndihmën e programit
    <em>Lokalize</em>.
  </li>
  <li>Për të parë se si duket përkthimi, mund të përdorësh këto komanda:
    <ul>
      <li>
	<strong>msgfmt -o kubrick.mo kubrick.po</strong>
      </li>
      <li>
	<strong>sudo cp kubrick.mo /usr/share/locale-langpack/sq/LC_MESSAGES/</strong>
      </li>
      <li>Pastaj hape programin
	<em>kubrik</em> dhe ndrysho gjuhën (te
	<em>Hdihmë &gt; Ndrysho Gjuhën...</em>).
      </li>
    </ul>
  </li>
  <li>Kur ta kesh mbaruar përkthimin (ose kur të jesh lodhur apo mërzitur dhe do që ta lësh), ma dërgo mua skedarin
    <strong>kubrick.po</strong>, aq sa të kesh përkthyer, që ta çoj te serverat e ubuntu-së.
  </li>
</ol>
<p>Mirë është që të instalohet edhe Fjalori Drejtshkrimor (shiko:&nbsp;
  <a href="https://l10n.org.al/fjalori-drejtshkrimor">https://l10n.org.al/fjalori-drejtshkrimor</a>) i cili ndihmon për të korrigjuar gabimet e shkrimit.</p>
<p>Po qe se të del ndonjë problem ose vështirësi mund të më kontaktosh për ndihmë (ose shkruaj një koment në fund të kësaj faqes).</p>
';

$node = node_submit($node);
node_save($node);

/* ---------------------------- */

$node = new stdClass();
$node->type = 'book';
node_object_prepare($node);

$node->title = 'Instalimi i Gjuhës Shqipe në Ubuntu';
$node->path = array('alias' => 'ubuntu-shqip');
$node->book['bid'] = $book_id;
$node->language = LANGUAGE_NONE;
$node->body[LANGUAGE_NONE][0]['format']  = 'full_html';
$node->body[LANGUAGE_NONE][0]['value']   = '
<p>Nëse ke lidhje me internetin, gjuha shqipe mund të instalohet shumë
kollaj:</p>
<ol style="margin-top: 0.25em; margin-right: 0px; margin-bottom: 0.25em; margin-left: 2em; border-style: initial; border-color: initial; vertical-align: baseline; list-style-type: decimal; list-style-position: initial; list-style-image: initial; border-width: 0px; padding: 0px;">
  <li style="border-style: initial; border-color: initial;
  vertical-align: baseline; border-width: 0px; padding: 0px; margin:
  0px;">Hap një terminal (<strong style="border-style: initial;
  border-color: initial; vertical-align: baseline; border-width: 0px;
  padding: 0px; margin: 0px;">Ctrl+Alt+t</strong>) dhe jep
  komandën:&nbsp;<strong style="border-style: initial; border-color:
  initial; vertical-align: baseline; border-width: 0px; padding: 0px;
  margin: 0px;">sudo apt-get install
  language-pack-sq</strong>&nbsp;(pastaj jep fjalëkalimin tënd).
  </li>
  <li style="border-style: initial; border-color: initial;
  vertical-align: baseline; border-width: 0px; padding: 0px; margin:
  0px;">Pasi të instalohet, duhet aktivizuar. Për këtë duhet të dalësh
  (logout), dhe kur të hysh përsëri (login), zgjidh gjuhën shqipe te
  menuja poshtë (si në figurë).
  </li>
</ol>
<p style="border-style: initial; border-color: initial;
vertical-align: baseline; border-top-width: 0px; border-right-width:
0px; border-bottom-width: 0px; border-left-width: 0px; padding-top:
0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px;
margin-top: 0px; margin-right: 0px; margin-bottom: 0px; margin-left:
0px; text-align: center; ">&nbsp;<img alt="Zgjidh gjuhën shqipe në
login" src="img/choose-albanian-language.jpg" style="vertical-align:
text-top; height: 146px; width: 300px; " /></p>
';
$node = node_submit($node);
node_save($node);

/* ---------------------------- */

$node = new stdClass();
$node->type = 'book';
node_object_prepare($node);

$node->title = 'Instalimi i Tastierës Shqipe në Ubuntu';
$node->path = array('alias' => 'tastiera-shqipe');
$node->book['bid'] = $book_id;
$node->language = LANGUAGE_NONE;
$node->body[LANGUAGE_NONE][0]['format']  = 'full_html';
$node->body[LANGUAGE_NONE][0]['value']   = '
<p>Fillimisht hapim <em>Preferimet e Tastierës</em>, te
menuja&nbsp;<strong>Sistemi &gt; Preferencat &gt;
Tastiera</strong>&nbsp;(ose&nbsp;<strong>System &gt; Preferences &gt;
Keyboard</strong>). Kjo mund të hapet edhe që nga Terminali
(<strong>Ctrl+Alt+t</strong>) me anë të
komandës&nbsp;<strong>gnome-keyboard-properties</strong>.</p>

<p style="text-align: center;"><img alt="Preferimet e Tastierës"
height="527" src="img/preferimet-e-tastieres.png" width="772" /></p>

<p style="text-align: left;">Aty shtojmë tastierën shqipe
(Shqipëria).</p>

<p style="text-align: left;">Pas kësaj, në shiritin sipër na del një
ikonë tastiere, ku mund të ndryshohet planimetria e tastierës:</p>

<p style="text-align: center;"><img alt="Ndryshimi i Planimetrisë së
Tastierës" height="139" src="img/change-keyboard-layout.png"
style="border: 1px solid black;" width="520" /></p>

<p style="text-align: left;">Në planimetrinë shqipe,
shkronja <strong>ë</strong> nxirret te <strong>;</strong> , kurse
shkronja <strong>ç</strong> nxirret te <strong>[</strong> . Për të
parë se ku janë shkronjat e tjera mund të hapet <em>Show Current
Layout</em>:</p>

<p style="text-align: left;"><img alt="Planimetria e Tastierës Shqipe"
height="389" src="img/albanian-keyboard-layout.png" style="display:
block; margin-left: auto; margin-right: auto;" width="776" /></p>
';
$node = node_submit($node);
node_save($node);

/* ---------------------------- */

$node = new stdClass();
$node->type = 'book';
node_object_prepare($node);

$node->title = 'Instalimi i Fjalorit Drejtshkrimor';
$node->path = array('alias' => 'fjalori-drejtshkrimor');
$node->book['bid'] = $book_id;
$node->language = LANGUAGE_NONE;
$node->body[LANGUAGE_NONE][0]['format']  = 'full_html';
$node->body[LANGUAGE_NONE][0]['value']   = '
<p><a href="http://www.shkenca.org/k6i/albanian_dictionary_for_aspell_sq.html">Fjalori
    i gjuhës shqipe për programin Aspell</a> (i cili përdoret për kontroll
  drejtshkrimor) përmban rreth 550.000 fjalë dhe trajta
  fjalësh. Instalimi bëhet me hapat e mëposhtëm:</p>
<ol>
  <li>Shkarkojeni fjalorin
    nga: <a href="http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2">http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2</a><br /><strong>wget
    http://www.shkenca.org/shkarkime/aspell6-sq-1.6.4-0.tar.bz2</strong>
  </li>
  <li>Shpaketojeni skedarin e porsashkarkuar:<br /><strong>tar -xvjf
    aspell6-sq-1.6.4-0.tar.bz2</strong>
  </li>
  <li>Kaloni te
    direktoria <strong>aspell6-sq-1.6.4-0</strong>:<br /><strong>cd
    aspell6-sq-1.6.4-0</strong>
  </li>
  <li>Instalimi i fjalorit bëhet me
    komandat:<br /><strong>./configure<br />make<br />sudo make
    install</strong>
  </li>
</ol>
<p>Mund të instaloni gjithashtu edhe këtë add-on për Firefox dhe
Thunderbird:&nbsp;<a href="https://addons.mozilla.org/en-US/thunderbird/addon/albanian-dictionary/">https://addons.mozilla.org/en-US/thunderbird/addon/albanian-dictionary/</a></p>
';
$node = node_submit($node);
node_save($node);

/* ---------------------------- */

$node = new stdClass();
$node->type = 'blog';
node_object_prepare($node);

$node->title = 'Visualization of Translating GNOME Into Albanian';
$node->language = LANGUAGE_NONE;
$node->body[LANGUAGE_NONE][0]['format']  = 'full_html';
$node->body[LANGUAGE_NONE][0]['value']   = '
<p><iframe class="youtube-player" frameborder="0" height="385" src="http://www.youtube.com/embed/ThZoTGBB-m8" type="text/html" width="640"></iframe></p><p>Recently I generated this video that shows the activity of translating GNOME projects into Albanian during the last years. This visualization was generated by Gource <a href="http://code.google.com/p/gource/">http://code.google.com/p/gource/</a> .</p>

<p>Gource is very easy to use, just install it: <b>apt-get install gource</b>, go to the project directory, and type: <b>gource</b>. However, in the case of GNOME translations this does not generate something useful. The problem is not with gource but rather with the structure of the projects. Each translation project has its own repository, so it is not easy to generate a general view for all the projects. Besides this, each translation project has data for all the languages, and I would like to visualize only the data about the Albanian translations.</p>

<p>Here I describe the steps and data processing that I did to generate this visualization.</p>

<ol><li>Checkout all the GNOME projects (translation files):
<pre language="bash">
mkdir GNOME/
cd GNOME/
svn_gnome=http://svn.gnome.org
gnome_modules=$(wget -o /dev/null -O- $svn_gnome/viewvc/ | grep \'a href="/viewvc/[^"]\' | sed \'s#.*/viewvc/\([^/]*\)/.*#\1#\')
for module in $gnome_modules; do svn checkout $svn_gnome/svn/$module/trunk/po $module; done
cd .. </pre>
</li><li>Generate gource log files for each of the projects:
<pre language="bash">
for dir in $(ls GNOME/); do echo $dir; cd GNOME/$dir/; gource --output-custom-log $dir.log; done
</pre>
</li><li>For each log file replace the word <i>trunk</i> with the name of the project (name of the directory), and concatenate all of them in a single big file:
<pre language="bash">
find GNOME -name \'*.log\' > gnome_log.txt
for file in $(find GNOME/ -name \'*.log\'); do echo $file; dir=$(dirname $file); cat $file | sed -e "s,/trunk/,/$dir/," >> GNOME.log; done
</pre>
</li><li>Now extract all the log lines related to Albanian translations:
<pre language="bash">
cat GNOME.log | grep "sq.po" > GNOME_sq.log
</pre>
</li><li>Remove the directory <i>/po/</i> from the names of the files inside the logs:
<pre language="bash">
sed -e \'s,/po/.*,,\' -i GNOME_sq.log
</pre>
</li><li>Order them according to the time of the file modification:
<pre language="bash">
sort -t'|' -k 1,1n -o GNOME.sq.log GNOME_sq.log
rm GNOME_sq.log
</pre>
</li><li>Create the visualization movie with gource and transform it in a suitable format for uploading to YouTube:
<pre language="bash">
gource GNOME.sq.log -s 0.1 -i 0 --max-files 0 --date-format "%B %Y" -640x360 -o - \
  | ffmpeg -y -r 25 -f image2pipe -vcodec ppm -i - -vcodec libvpx -b 10000K GNOME.sq.webm
</pre>
</li></ol>
';
$node = node_submit($node);
node_save($node);

/* ---------------------------- */

$node = new stdClass();
$node->type = 'page';
node_object_prepare($node);

$node->title = 'About';
$node->path = array('alias' => 'about');
$node->menu = array(
  'enabled' => 1,
  'module' => 'menu',
  'link_title' => 'About',
  'parent' => 'main-menu:0',
  'weight' => 20,
  'menu_name' => 'main-menu',
);
$node->language = LANGUAGE_NONE;
$node->body[LANGUAGE_NONE][0]['format']  = 'full_html';
$node->body[LANGUAGE_NONE][0]['summary']   = '
Kjo faqe ka si qëllim të ndihmojë dhe të koordinojë përkthimin e programeve kompjuterike në gjuhën shqipe. (...së shpejti)

<iframe src="http://www.facebook.com/plugins/likebox.php?href=http%3A%2F%2Fwww.facebook.com%2FE.Duam.Kompjuterin.Shqip&amp;width=600&amp;colorscheme=light&amp;show_faces=true&amp;border_color&amp;stream=true&amp;header=false&amp;height=550" scrolling="no" frameborder="0" style="border:none; overflow:hidden; width:600px; height:550px;" allowTransparency="true"></iframe>
';
$node->body[LANGUAGE_NONE][0]['value']   = '
Kjo faqe ka si qëllim të ndihmojë dhe të koordinojë përkthimin e programeve kompjuterike në gjuhën shqipe. (...së shpejti)

<iframe src="http://www.facebook.com/plugins/likebox.php?href=http%3A%2F%2Fwww.facebook.com%2FE.Duam.Kompjuterin.Shqip&amp;width=600&amp;colorscheme=light&amp;show_faces=true&amp;border_color&amp;stream=true&amp;header=false&amp;height=550" scrolling="no" frameborder="0" style="border:none; overflow:hidden; width:600px; height:550px;" allowTransparency="true"></iframe>';
$node = node_submit($node);
node_save($node);

/* ---------------------------- */

$node = new stdClass();
$node->type = 'blog';
node_object_prepare($node);

$node->title = 'Updating Drupal With Drush';
$node->language = LANGUAGE_NONE;
$node->body[LANGUAGE_NONE][0]['format']  = 'plain_text';
$node->body[LANGUAGE_NONE][0]['value']   = '
First, backup the sites. Then give the following commands:

drush -l site1.com vset --yes maintenance_mode 0
drush -l site2.com vset --yes maintenance_mode 0
drush -l site1.com cache-clear all
drush -l site2.com cache-clear all
drush up
drush -l site1.com updb
drush -l site1.com up
drush -l site1.com vset --yes maintenance_mode 1
drush -l site2.com updb
drush -l site2.com up
drush -l site2.com vset --yes maintenance_mode 1

Finally restore the sites again.

------------------

I take a very lazy approach that is quite foolproof. Instead of making a patch I go the route of finding all changed files and replacing them, not replacing any files that were untouched. It leaves the /sites folder undisturbed among other things too.

1. Navigate to Drupal root
2. wget drupal-x.xx.tar.gz
3. tar -xzvf drupal-x.xx.tar.gz
4. cd drupal-x.xx
5. \cp -Rvupf * ../

The cp command with those flags does all that was said above. Flawless core upgrade every time.

--------------------

References:
http://cafuego.net/2011/05/27/how-do-you-update-drupal
';
$node = node_submit($node);
node_save($node);

?>