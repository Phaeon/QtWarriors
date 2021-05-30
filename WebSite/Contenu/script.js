$(document).ready(function(){
    $(".dropdown-trigger").dropdown();
    $('.carousel.carousel-slider').carousel({
        dist: 0,
        padding: 0,
        fullWidth: false,
        indicators: true,
        duration: 100,
        
      });

      autoplay();

      switch($_GET_PATH()){
        case 'Annexe':
                $('#annexe').addClass('active');          
                break;
        case 'Bilan':
                $('#bilan').addClass('active');          
                break;
        case 'IA':
                $('#ia').addClass('active');          
                break;
        case 'Modelisation':
                $('#modelisation').addClass('active');          
                break;
      }

      $('.slider').slider({
        el: 2,
        interval: 10000000
      });
      $('.materialboxed').materialbox();
});

function autoplay() {
  $('.carousel').carousel('next');
  setTimeout(autoplay, 9000);
}

function $_GET_PATH() {
  var path = window.location.href.split("/");
  return path[4] ? path[4] : null;
}