<?php

function emailanonymizer_custom_comment_submit($form, $form_state) {
  if ($form_state['values']['expose_fake_email']) {
    $name = $form_state['values']['name'];
    $original_email = $form_state['values']['mail'];
    $encoded_email = emailanonymizer_generate_address();
    $created = date("F j, Y, g:i a");
    db_query('INSERT INTO {emailanonymizer_email_mapping} (created, sender_name, original_email, encoded_email) VALUES ("%d", "%s", "%s","%s")', $created, $name, $original_email, $encoded_email);
  }
}