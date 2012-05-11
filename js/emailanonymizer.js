Drupal.behaviors.emailanonymizer = function(context) {

   $('#edit-email-to-anonymize-wrapper').hide();
   $('#edit-name-1-wrapper').hide();
   $('#edit-expose-fake-email').change(function(){
   if($(this).attr('checked') == true){
     $('#edit-email-to-anonymize-wrapper').slideDown();
     $('#edit-name-1-wrapper').slideDown();
   }
   else {
     $('#edit-email-to-anonymize-wrapper').slideUp();
     $('#edit-name-1-wrapper').slideUp();
   }
   });
}