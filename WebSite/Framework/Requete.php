<?php
namespace Framework;

class Requete {

    private $parametres;

    public function __construct($parametres) {
        $this->parametres = $parametres;
    }

    public function existeParametre($nom) {
        return (isset($this->parametres[$nom]) && $this->parametres[$nom] != "");
    }

    public function getParametre($nom) {
        if ($this->existeParametre($nom)) {
            return $this->parametres[$nom];
        }
        else {
            return "";
            //throw new Exception("Paramètre '$nom' absent de la requête");
        }
    }

}

