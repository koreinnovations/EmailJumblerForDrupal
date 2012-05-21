<?php

function theme_emailanonymizer_contact_link($record) {
  $output = '';

  $output .= '<p>';

  if ($record->show_anonymized) {
    $output .= t('You may contact this anonymous person using the following address: ');
    $output .= l($record->encoded_email, 'mailto:' . $record->encoded_email, array('absolute' => TRUE));
  }
  else {
    $output .= t('You may contact this person using the following information: ');
    $output .= $record->sender_name . ' - ' . l($record->original_email, 'mailto:' . $record->original_email, array('absolute' => TRUE));
  }

  $output .= '</p>';

  return $output;
}