Drupal.behaviors.trivia = {
  attach: function (context, settings) {
  	function waitplayer(request) {
       jQuery.ajax({
            type: "POST",
            url: 'ajax_reply',
            success: function(data) {
                jQuery('#time-execution').text(data);
                 if (!jQuery('.wait-time-please').length) {
                   jQuery( ".intervalos-tiempo" ).prepend( "<div class='wait-time-please'>你的对手还没有完成呢，</div>");
                   jQuery('.intervalos-tiempo').prepend('<img id="img-time-op" src="sites/all/themes/custom/trivia/img/gif/reloj.gif"/>');
                 }
                var result = data.search('winning-player');
                if (result == false) {
                  window.location.replace(data);
                }
            }
        });
    }
    setInterval(waitplayer, 3000, Drupal.settings.trivia);
  }
};