<?php
/**
 * @file
 * Import translations from PO files.
 */

/**
 * Menu callback for 'translations/import'.
 * Import translations from PO files.
 */
function btrClient_import() {
  return drupal_get_form('btrClient_import_form');
}

/**
 * Import form.
 */
function btrClient_import_form($form, &$form_state) {
  $form = array(
    '#prefix' => '<div class="btr-ui-filter clear-block">',
    '#suffix' => '</div>',
  );

  $form['import'] = array(
    '#type' => 'fieldset',
    '#title' => t('Import PO files'),
    '#description' => t('
<p>Importing translations from PO files is like a bulk translation and
voting service. For any translation in the PO files, it will be added
as a suggestion if such a translation does not exist, or it will just
be voted if such a translation already exists. In case that the
translation already exists but its author is not known, then you (the
user who makes the import) will be recorded as the author of the
translation.</p>

<p>This functionality can be useful if you prefer to work off-line
with PO files. You can export the PO files of a project, work on them
with desktop tools (like Lokalize) to translate or correct exported
translations, and then import back to B-Translator the
translated/corrected PO files.</p>
'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['import']['translation_file'] = array(
    '#type' => 'file',
    '#description' => t('Upload a PO file. If you have many files, upload them as an archive (tar, tgz, bz2, 7z, zip).'),
  );

  $form['buttons'] = array(
    //'#prefix' => '<div class="import-submit">',
    //'#suffix' => '</div>',
  );
  $form['buttons']['submit'] = array(
    '#value' => t('Upload'),
    '#type' => 'submit',
  );

  return $form;
}

function btrClient_import_form_validate($form, &$form_state) {
  $file_name = $_FILES['files']['name']['translation_file'];
  $file_type = $_FILES['files']['type']['translation_file'];
  $file_tmp_name = $_FILES['files']['tmp_name']['translation_file'];
  $file_error = $_FILES['files']['error']['translation_file'];
  $file_size = $_FILES['files']['size']['translation_file'];

  $extensions = 'po tar gz tgz bz2 xz 7z zip';
  $regex = '/\.(' . preg_replace('/ +/', '|', preg_quote($extensions)) . ')$/i';
  if (!preg_match($regex, $file_name)) {
    form_set_error('file',
      t('Only files with the following extensions are allowed: %files-allowed.',
        array('%files-allowed' => $extensions))
    );
    return;
  }

  $known_file_types = array(
    'text/x-gettext-translation',
    'application/x-tar',
    'application/x-compressed-tar',
    'application/x-bzip',
    'application/x-7z-compressed',
    'application/zip',
  );
  if (!in_array($file_type, $known_file_types)) {
    form_set_error('file',
      t('File has unknown type: %file_type.',
        array('%file_type' => $file_type))
    );
    return;
  }

  if ($file_error != 0) {
    form_set_error('file',
      t("Error %error happened during file upload.",
        array('%error' => $file_error))
    );
    return;
  }

  /*
  $file = file_save_upload('pofile', array(
      'file_validate_extensions' => array('po tar gz tgz bz2 xz 7z zip'),
  ));
  if (!$file) {
    form_set_error('file', t('No file was uploaded.'));
    return;
  }

  if ($file = file_move($file, 'temporary://')) {
    $form_state['values']['import']['file'] = $file;
  }
  else {
    form_set_error('file', t('Failed to write the uploaded file the site\'s file folder.'));
  }
  */
}


function btrClient_import_form_submit($form, &$form_state) {
  $file_name = $_FILES['files']['name']['translation_file'];
  $file_type = $_FILES['files']['type']['translation_file'];
  $file_tmp_name = $_FILES['files']['tmp_name']['translation_file'];
  $file_error = $_FILES['files']['error']['translation_file'];
  $file_size = $_FILES['files']['size']['translation_file'];

  /*
  $file=$form_state['values']['import']['file'];
  unset($form_state['values']['import']['file']);
  //$file->status = FILE_STATUS_PERMANENT;
  //file_save($file);
  */
  drupal_set_message(
    t("The file '@filename' was uploaded successfully.",
      array('@filename' => $file_name))
  );
}