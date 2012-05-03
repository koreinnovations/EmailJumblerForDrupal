<?php

function ssi_uc_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'comment_form') {
     $form['#submit'][] = 'custom_comment_email_anonymization';
  }
}

function custom_comment_email_anonymization($form, &$form_state) {
$name = $form_state['values']['name'];
$original_email = $form_state['values']['mail'];
$encoded_email = emailanonymizer_generate_address();
$created = date("F j, Y, g:i a");
db_query('INSERT INTO {emailanonymizer_email_mapping} (created, sender_name, original_email, encoded_email) VALUES ("%d", "%s", "%s","%s")', $created, $name, $original_email, $encoded_email);
}