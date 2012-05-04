<?php

function theme_emailanonymizer_contact_link($record) {
  $output = '';

  $output .= '<p>';
  $output .= t('You may contact this person using the following address: ');
  $output .= l($record->encoded_email, 'mailto:' . $record->encoded_email, array('absolute' => TRUE));
  $output .= '</p>';

  return $output;
}