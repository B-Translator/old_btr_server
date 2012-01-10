<?php
/**
 * Functions that are common for all the pages.
 */

/**
 * Returns an array of languages and their details.
 */
function l10n_suggestions_get_languages() {

  $arr_langs = array(
    'fr' => array(
      'code' => 'fr',
      'name' => 'French',
      'encoding' => 'latin1',
      'direction' => LANGUAGE_LTR,
      'plurals' => 2,
    ),
    'sq' => array(
      'code' => 'sq',
      'name' => 'Albanian',
      'encoding' => 'latin1',
      'direction' => LANGUAGE_LTR,
      'plurals' => 2,
    ),
  );

  return $arr_langs;
}

function send_html_mail($from_name, $from_email, $to, $subject, $html_message, $text_message)
{
  $subject = '=?UTF-8?B?'.base64_encode($subject).'?=';

  $semi_rand = md5(time());
  $mime_boundary = "==Multipart_Boundary_x{$semi_rand}x";

  $headers = "From: $from_name <$from_email>
Reply-To: $from_email
MIME-Version: 1.0
Content-Type: multipart/alternative; boundary=\"$mime_boundary\"
";

  $body = "MIME-Version: 1.0
Content-Type: multipart/alternative; boundary=\"$mime_boundary\"

This is a multi-part message in MIME format.

--$mime_boundary
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: quoted-printable

$text_message
--$mime_boundary
Content-Type: text/html; charset=UTF-8
Content-Transfer-Encoding: quoted-printable

$html_message

--$mime_boundary--
";

  return mail($to, $subject, $body, $headers);
}
?>