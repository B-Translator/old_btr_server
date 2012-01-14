<?php
/**
 * Modify the drupal mail system to send HTML emails.
 * See: http://drupal.org/node/900794
 */
class HTMLMailSystem implements MailSystemInterface {
  /**
   * Concatenate and wrap the e-mail body for plain-text mails.
   *
   * @param $message
   *   A message array, as described in hook_mail_alter().
   *
   * @return
   *   The formatted $message.
   */
  public function format(array $message) {
    $subject = '=?UTF-8?B?'.base64_encode($message['subject']).'?=';

    $semi_rand = md5(time());
    $mime_boundary = "==Multipart_Boundary_x{$semi_rand}x";

    $from_email = $message['headers']['From'];
    $message['headers']['MIME-Version'] = '1.0';
    $message['headers']['Content-Type'] = "multipart/alternative; boundary=\"$mime_boundary\"";

    $text_message = $message['body_text'];
    $html_message = $message['body_html'];
    $message['body'] = "MIME-Version: 1.0
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
    return $message;
  }

  /**
   * Send an e-mail message, using Drupal variables and default settings.
   *
   * @see <a href="http://php.net/manual/en/function.mail.php
" title="http://php.net/manual/en/function.mail.php
" rel="nofollow">http://php.net/manual/en/function.mail.php
</a>   * @see drupal_mail()
   *
   * @param $message
   *   A message array, as described in hook_mail_alter().
   * @return
   *   TRUE if the mail was successfully accepted, otherwise FALSE.
   */
  public function mail(array $message) {

    $to = $message['to'];
    $subject = $message['subject'];
    $body = $message['body'];

    // Build headers.
    $arr_headers = array();
    foreach ($message['headers'] as $name => $value) {
      $arr_headers[] = $name . ': ' . mime_header_encode($value);
    }
    $headers = join("\n", $arr_headers);

    // Send the mail and return the result.
    return mail($to, $subject, $body, $headers);
  }
}
?>