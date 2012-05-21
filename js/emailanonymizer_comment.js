Drupal.behaviors.emailanonymizer = function(context) {
  
  var emailField = $('#edit-mail-wrapper');
  var nameField = $('#edit-name-wrapper');

  var updateContactFieldsVisibility = function() {
    var radio = $('input:radio[name="contact_pref"]:checked').val();
    if (radio == "no_anonymize" || radio == "anonymize") {
      emailField.slideDown();
      nameField.slideDown();
    }
    else {
      emailField.slideUp();
      nameField.slideUp();
    }
  };

  updateContactFieldsVisibility();
  $('input:radio[name="contact_pref"]').click(updateContactFieldsVisibility);

}