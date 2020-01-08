Drupal.behaviors.time = {
  attach: function (context, settings) {
  	// Logout Game
  	function player_logout(request) {
       jQuery.ajax({
            type: "POST",
            url: 'ajax_logout',
            success: function(data) {
            	console.log('Finish Game');
            	location.reload();
            }
        });
    }
	// Get Full time Quiz
	const total_seg = Drupal.settings.trivia.fulltimequiz;
	// % 100 Start
	const porcentaje = 100; // Porcentaje
	// Get time trivia
	var time = jQuery('.hasCountdown').text().split('Time left: ');
	// Get text time 
	var a = time[1].split(':'); 
	// Convert time to Seg
	let segundos = (+a[0]) * 60 * 60 + (+a[1]) * 60 + (+a[2]); 
	// Interval Function By (1 Seg)
	var counterBack = setInterval(function () {
		segundos--;
		if (segundos > 0) {
			var ancho = (segundos*porcentaje)/total_seg;
		  	jQuery('.progress-bar').css('width', ancho + '%');
		} else {
		  clearInterval(counterBack);
		  jQuery('.progress-bar').css('width', '0%');
		  setInterval(player_logout, 1000);
		}
	}, 1000);
  }
};