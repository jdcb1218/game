jQuery(document).ready(function(){
	jQuery(".imagen-quiz").append("<div class='img-borde'></div>");
	jQuery("label:contains('Choose one')" ).css( "display", "none" );
	// Questions multichoice-row
	jQuery('.multichoice-row.correct.jquery-once-1-processed').click(function() {
	   jQuery('#edit-navigation').show();
	   if (jQuery('.status-answer').length) {
	   	  jQuery(".status-answer").text("正确");
		  jQuery("." + jQuery(this).context.classList[1] + ' ' + '.img-borde').addClass("correcta");
		  jQuery(".answering-form").append(jQuery("#edit-navigation"));
 	   }else{
	   	  jQuery( ".field-type-text-with-summary" ).prepend("<div class='status-answer'>正确</div>");	
	 	  jQuery("." + jQuery(this).context.classList[1] + ' ' + '.img-borde').addClass("correcta");
	 	}
	});
	jQuery('.multichoice-row.incorrect.jquery-once-1-processed').click(function() {
	   jQuery('#edit-navigation').hide();
	   if (jQuery('.status-answer').length) {
	   	  jQuery(".status-answer").text("不正确的");
		  jQuery("." + jQuery(this).context.classList[1] + ' ' +  '.img-borde').addClass("incorrecta");
	   	  jQuery('#myModal').modal();
	   	  jQuery("#myModal").append(jQuery("#edit-navigation"));
	   	  jQuery('#edit-navigation').show();
	   }else{
	      jQuery( ".field-type-text-with-summary" ).prepend("<div class='status-answer'>不正确的</div>");
		  jQuery("." + jQuery(this).context.classList[1] + ' ' + '.img-borde').addClass("incorrecta");
		  jQuery('#myModal').modal(); 	
		  jQuery("#myModal").append(jQuery("#edit-navigation"));
		  jQuery('#edit-navigation').show();
		}
	});

	// Questions True // False
	jQuery('.quiz-question-truefalse .correct').click(function() {
		jQuery('#edit-navigation').show();
		jQuery(".answering-form").append(jQuery("#edit-navigation"));
	});
	jQuery('.quiz-question-truefalse .incorrect').click(function() {
		jQuery("#quiz-question-answering-form").append(jQuery("#myModal"));
		jQuery("#myModal").append(jQuery("#edit-navigation"));
		jQuery('#myModal').modal();
		jQuery('#edit-navigation').show();
	});	

	jQuery("#block-trivia-time").hide();
  	function showtime(request) {
  		jQuery("#block-trivia-time").show();
    }
    setInterval(showtime, 1000);
});