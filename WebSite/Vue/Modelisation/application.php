<?php $this->titre = "Modélisation de l'application"; ?>
<div class="row">
    <div class="col s1"></div>
    <div class="col s10">
        <h4>Modélisation de l'application</h4>
        <div class="divider"></div>
        <h5><u>Principe du Modèle Vue Contrôleur</u></h5>
        <div class="section">   
            <p>Les rôles de ces trois entités sont donc les suivantes : <p>
            <ul class="ul_Context">
                    <li class="ul_empty"><b>Modèle :</b> accès et gestion des données.</li>
                    <li class="ul_empty"><b>Vue :</b> interface utilisateur (entrées et sorties).</li>
                    <li class="ul_empty"><b>Contrôleur :</b> gestion des événements et synchronisation.</li>
            </ul>  
        </div>

        <h5><u>Pourquoi le MVC</u></h5>
        <div class="section">  
            <ul class="ul_Context">
                    <li class="ul_empty">Organisation du projet.</li>
                    <li class="ul_empty">Rôles de chaque fichier.</li>
            </ul>   
        </div>
        <h5><u>Les modèles</u></h5>
        <div class="section">
            <ul class="ul_Context">
                        <li>
                            <h5 class="light black-text text-lighten-3 mycolor">Start : </h5>
                            <ul class="ul_Context">
                                <li class="ul_empty">Difficulté.</li>
                                <li class="ul_empty">Nom du joueur.</li>
                            </ul> 
                        </li>
                        <li>
                            <h5 class="light black-text text-lighten-3 mycolor">Choose : </h5>
                            <ul class="ul_Context">
                                <li class="ul_empty">Liste des monstres.</li>
                            </ul>
                        </li>
                        <li>
                            <h5 class="light black-text text-lighten-3 mycolor">Player : </h5>
                            <ul class="ul_Context">
                                <li class="ul_empty">Liste des monstres pour chaque joueur.</li>
                            </ul>
                        </li>
                        <li>
                            <h5 class="light black-text text-lighten-3 mycolor">Game : </h5>
                            <ul class="ul_Context">
                                <li class="ul_empty">Stocke le plateau.</li>
                            </ul>
                        </li>
                        <h5 class="light black-text text-lighten-3 mycolor">Pawn : </h5>
                            <ul class="ul_Context">
                                <li class="ul_empty">Statistiques du pion.</li>
                                <li class="ul_empty">Modélisation du monstre 3D.</li>
                            </ul>
                        </li>
            <ul>
        </div>
        <h5><u>Les vues</u></h5>
        <div class="section">
                    <ul class="ul_Context">
                        <li>
                            <h5 class="light black-text text-lighten-3 mycolor">StartView : </h5>
                            <ul class="ul_Context">
                                <li class="ul_empty">Choix du nom.</li>
                                <li class="ul_empty">Choix de la difficulté.</li>
                            </ul>
                        </li>
                        <li>
                            <h5 class="light text-lighten-3">ChooseView et ChooseGL : </h5>
                            <ul class="ul_Context">
                                <li class="ul_empty">Choix des monstres.</li>
                            </ul>
                        </li>
                        <li>
                            <h5 class="light mycolor text-lighten-3">GameView : </h5>
                            <ul class="ul_Context">
                                <li class="ul_empty">Affichage du jeu.</li>
                                <li class="ul_empty">Affichage des monstres.</li>
                                <li class="ul_empty">Affichage des informations concernant les monstres.</li>
                                <li class="ul_empty">Affichage de la flèche permettant de choisir un emplacement où jouer.</li>
                            </ul>
                        </li>
                        <li>
                            <h5 class="light mycolor text-lighten-3">EndGameView : </h5>
                            <ul class="ul_Context">
                                <li class="ul_empty">Descriptif de fin de partie.</li>
                            </ul>
                        </li>
                </ul>
        </div>
        <h5><u>Les contrôleurs</u></h5>
        <div class="section">
            <ul class="ul_Context">
                        <li>
                            <h5 class="light black-text text-lighten-3 mycolor">Controller : </h5>
                            <ul class="ul_Context">
                                <li class="ul_empty">Administre les vues.</li>
                            </ul>
                        </li>
                        <li>
                            <h5 class="light black-text text-lighten-3 mycolor">GameManagment : </h5>
                            <ul class="ul_Context">
                                <li class="ul_empty">Administre le jeu.</li>
                            </ul>
                        </li>
            <ul>
        </div>
        <h5><u>OpenGLWidget</u></h5>
        <div class="section">
                <ul class="ul_Context">
                        <li class="ul_empty">Les monstres alliés et ennemis.</li>
                        <li class="ul_empty">Le plateau.</li>
                        <li class="ul_empty">La flèche.</li>
                </ul>
        </div>
        <h5><u>Problèmes rencontrés</u></h5>
        <div class="section">
            <ul class="ul_Context">
                <li class="ul_empty">Le MVC.</li>
                <li class="ul_empty">La fusion.</li>
                <li class="ul_empty">OpenGL et Qt.</li>
                <li class="ul_empty">Traduction de l'application.</li>
            </ul>
        </div>
    </div>
    <div class="col s1"></div>
</div>