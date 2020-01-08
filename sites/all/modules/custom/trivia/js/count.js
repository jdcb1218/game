Drupal.behaviors.count = {
  attach: function (context, settings) {
	var n = 3;
	var l = document.getElementById("count-list");
	setInterval(function(){
	  l.innerHTML = n;
	  n--;
	  if(n == false || n < 0){
	  	var link = jQuery('.quiz-start-link').attr('href');
	  	window.location.replace(link);
	  }
	},2000); 
  }
};