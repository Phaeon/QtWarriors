<?php
namespace Framework;

use Framework\Configuration;
use Exception;
//require_once 'Configuration.php';

class Vue {

    /** Nom du fichier associé à la vue */
    private $fichier;

    /** Titre de la vue (défini dans le fichier vue) */
    private $titre;

    public function __construct($action, $controleur = "") {
        // La convention de nommage des fichiers vues est : Vue/<$controleur>/<$action>.php
        $fichier = "Vue/";
        if ($controleur != "") {
            $fichier = $fichier . $controleur . "/";
        }
        $this->fichier = $fichier . $action . ".php";
    }

    public function generer($donnees) {
        // Génération de la partie spécifique de la vue
        $contenu = $this->genererFichier($this->fichier, $donnees);

        $racineWeb = Configuration::get("racineWeb", "/");
        // Génération du gabarit commun utilisant la partie spécifique
        $vue = $this->genererFichier('Vue/gabarit.php',
                array('titre' => $this->titre, 'contenu' => $contenu,
                    'racineWeb' => $racineWeb));
        echo $vue;
    }

    private function genererFichier($fichier, $donnees) {
        if (file_exists($fichier)) {
            // Rend les éléments du tableau $donnees accessibles dans la vue
            extract($donnees);
            // Démarrage de la temporisation de sortie
            ob_start();
            require $fichier;
            return ob_get_clean();
        }
        else {
            throw new Exception("Fichier '$fichier' introuvable");
        }
    }

    private function nettoyer($valeur) {
        return htmlspecialchars($valeur, ENT_QUOTES, 'UTF-8', false);
    }

}
