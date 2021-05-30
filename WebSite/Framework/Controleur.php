<?php

namespace Framework;

use Framework\Requete;
use Framework\Vue;
use Exception;

//require_once 'Requete.php';
//require_once 'Vue.php';


abstract class Controleur {

    /** Action à réaliser */
    private $action;
    
    /** Requête entrante */
    protected $requete;


    public function setRequete(Requete $requete)
    {
        $this->requete = $requete;
    }


    public function executerAction($action)
    {
        if (method_exists($this, $action)) {
            $this->action = $action;
            $this->{$this->action}();
        }
        else {
            $classeControleur = get_class($this);
            throw new Exception("Action '$action' non définie dans la classe $classeControleur");
        }
    }

    /**
     * Méthode abstraite correspondant à l'action par défaut
     * Oblige les classes dérivées à implémenter cette action par défaut
     */
    public abstract function index();


    protected function genererVue($donneesVue = array())
    {
        // Détermination du nom du fichier vue à partir du nom du contrôleur actuel
        $classeControleur = get_class($this);
        $controleur = str_replace("Controleur", "", $classeControleur);
        
        // Instanciation et génération de la vueF
        $vue = new Vue($this->action, $controleur);
        $vue->generer($donneesVue);
    }

    // Permets de vérifier que seul les personnes connectées peuvent accéder à la page
    protected function isConnect(){
        if(isset($_SESSION['valideConnexion']) && $_SESSION['valideConnexion'] == true){
            return true;
        }else {
            return  header("location:../");
        }
    }

// Permets de vérifier que seul le secretaire peut accéder à la page
    protected function SecretaireisConnected(){
        if(isset($_SESSION['valideConnexion']) && $_SESSION['valideConnexion'] == true &&  $_SESSION['type'] == 'secretaire'){
                return true;
        }else {
            return  header("location:../../");
        }
    }

// Permets de vérifier que seul l'entraineur peut accéder à la page
    protected function EntraineurisConnected(){
        if(isset($_SESSION['valideConnexion']) && $_SESSION['valideConnexion'] == true &&  $_SESSION['type'] == 'entraineur'){
                return true;
        }else {
                return  header("location:../../");
        }
    }

}
