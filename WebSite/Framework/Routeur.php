<?php
namespace Framework;

use Framework\Controleur;
use Framework\Requete;
use Framework\Vue;
use Exception;

//require_once 'Controleur.php';
//require_once 'Requete.php';
//require_once 'Vue.php';

class Routeur {

    public function routerRequete() {
        try {
            if(session_status() === PHP_SESSION_NONE){
                session_start();
            }

            $requete = new Requete(array_merge($_GET, $_POST));

            $controleur = $this->creerControleur($requete);
            $action = $this->creerAction($requete);

            $controleur->executerAction($action);
        }
        catch (Exception $e) {
            $this->gererErreur($e);
        }
    }

    private function creerControleur(Requete $requete) {
        // index.php?controleur=XXX&action=YYY&id=ZZZ

        $controleur = "Accueil";  // Contrôleur par défaut
        if ($requete->existeParametre('controleur')) {
            $controleur = $requete->getParametre('controleur');
            // Première lettre en majuscules
            $controleur = ucfirst(strtolower($controleur));
        }
        // La convention de nommage des fichiers controleurs est : Controleur/Controleur<$controleur>.php
        $classeControleur = "Controleur" . $controleur;
        $fichierControleur = "Controleur/" . $classeControleur . ".php";
        if (file_exists($fichierControleur)) {
            require($fichierControleur);
            $controleur = new $classeControleur();
            $controleur->setRequete($requete);
            return $controleur;
        }
        else {
            throw new Exception("Fichier '$fichierControleur' introuvable");
        }
    }

    private function creerAction(Requete $requete) {
        $action = "index";  // Action par défaut
        if ($requete->existeParametre('action')) {
            $action = $requete->getParametre('action');
        }
        return $action;
    }

    private function gererErreur(Exception $exception) {
        $vue = new Vue('erreur');
        $vue->generer(array('msgErreur' => $exception->getMessage()));
    }

}
