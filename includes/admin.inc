<?php

function emailanonymizer_admin_settings_form() {
  $form = array();

  $form['emailanonymizer_email_domain'] = array(
      '#title' => t('Email Domain Name'),
      '#type' => 'textfield',
      '#default_value' => emailanonymizer_get_domain(),
      '#description' => t('This will be the part of the anonymous email address after the @'),
  );

  return system_settings_form($form);
}