<!doctype html>
<html lang="fr">
    <head>
        <meta charset="UTF-8" />
        <base href="<?= $racineWeb ?>" >
        <meta name="viewport" content="width=device-width, initial-scale=1">
        
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
        <link type="text/css" rel="stylesheet" href="Contenu/style.css" />
        <script type="text/javascript" src="Contenu/script"></script>

        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css">
        <script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/js/materialize.min.js"></script>
        <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
      
       <title><?= $titre ?></title>
    </head>  

    <div class="navbar-fixed">
      <nav class="myColor">
        <div class="nav-wrapper">
          <a href="" class="brand-logo center">QtWarriors</a>
          <ul class="left hide-on-med-and-down">
            <li id="modelisation"><a class="dropdown-trigger" href="/" data-target="dropdown1">Modelisation<i class="material-icons right">arrow_drop_down</i></a></li>
            <li id="ia"><a class="dropdown-trigger" href="/" data-target="dropdown2">Intelligence Artificielle<i class="material-icons right">arrow_drop_down</i></a></li>
            <li id="bilan"><a href="Bilan/index">Bilan</a></li>
            <li id="annexe"><a href="Annexe/index">Annexes</a></li>
          </ul>
        </div>
      </nav>
    </div>

    <!-- Modelisation -->
    <ul id="dropdown1" class="dropdown-content">
      <li><a href="Modelisation/troisDimention">Modélisation 3D</a></li>
      <li class="divider"></li>
      <li><a href="Modelisation/application">Modélisation de l'application</a></li>
    </ul>
    <!-- Intelligence Artificielle -->
    <ul id="dropdown2" class="dropdown-content">
      <li><a href="Ia/alphaBeta">Alpha-Beta</a></li>
      <li class="divider"></li>
      <li><a href="Ia/automates">Automates</a></li>
    </ul>

    <body>
      <div id="global">
        <div class="container-fluid">
          <?= $contenu ?>
        </div>
      </div>
      <footer>
        <nav class="footer-copyright myColor">
            <div class="container center">
            <?= date('Y');?> Copyright
            <a class="myColor" href="Dl/index">Declaration sur l'honneur </a>
            </div>
        </nav>
      </footer>
    </body>
</html>
