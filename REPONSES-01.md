#Projet programmation orientée objet (SSV)

##REPONSES du groupe N°1 (Bruno Siniciali & Samuele Sattar) 

*************************************************
##Q1.1
On crée une méthode privée ' clamping() ' afin de favoriser l'encapsulation et pour permettre la réutilisation de l'algorithme par d'autres méthodes de la classe Collider
*************************************************
##Q1.2
Indiquer explicitement qu'on veut utiliser le constructeur par défaut indique qu'il ne s'agit pas d'un oubli de notre part qu'on veut utiliser le constructeur ou l'opérateur égal par défaut. Il est toujours utile d'indiquer cela explicitement au lecteur.
*************************************************
##Q1.3
Une boucle for qui itère sur les neuf versions candidates de "to" sert à trouver quelle est la distance la plus petite entre "from" et candidat pour ensuite trouver le parcours le plus court entre le deux points et mettre à jour le "positionCenter" avec les nouvelles coordonnées.
*************************************************
##Q1.4
Il nous semble judicieux de passer par référence constante les Vec2d et le Collider puisqu'il peut s'agir d'objets volumineux.
*************************************************
##Q1.5
Il nous semble judicieux d'utiliser le const pour les fonctions getPosition(), getRadius(), directionTo(const Vec2d&), directionTo(const Collider&), distanceTo(const Vec2d&), distanceTo(const Collider&).
*************************************************
##Q1.6
On peut éviter la duplication en utilisant operator> avec un Collider peut appeler isColliderInside() ; operator> avec un Vec2d peut appeler isPointInside() ; operator| peut appeler isColliding()
*************************************************
##Q1.7
Les opérateurs internes sont ' < ' , ' | ' , ' += ' puisque pour ceux-là on a besoin d'accéder aux objets courants de la classe (au *this).
L'opérateur externe est ' << ' puisqu'on doit surcharger l'opérateur d'affichage et on ne cherche pas à modifier la classe ostream.
*************************************************
##Q1.8
On veut éviter la copie inutile et garantir que les arguments Vec2d et Collider ne soient pas modifiés. Il est donc judicieux de les passer par référence constante.
*************************************************
##Q1.9
Les fonctions qui ne devront être codés avec const sont : isPointInside(...), isColliding(...), isColliderInside(...) et les surcharges d'opérateurs >, | car on ne veut pas modifier les objets passés en argument de ces méthodes.
*************************************************
##Q2.1
La méthode draw puisqu'elle ne modifie par les attributs et contente de les afficher.
*************************************************
##Q2.2
On doit pour cela supprimer l'opérateur d'affectation et le constructeur de copie. 
*************************************************
##Q2.3
On doit donc libérer la mémoire allouée aux animaux lors de la destruction de l'environnement. On doit donc ajouter la fonction clean dans le destructeur de l'environnement en libérant les espaces mémoires allouées aux animaux. 
*************************************************
##Q2.5
Les 2 méthodes sont: 

- calcul de la force d'attraction:
    - arguments nécessaires:
        - position de la cible qui doit être passé par référence constant pour éviter des copies inutiles et parce que la position de la cible n'est pas modifiée par la méthode ==> c'est la distance par rapport à la cible qui détermine 
    - type de retour: un vecteur correspondant à la force exercée
    - méthode doit être const car elle ne modifie pas l'objet donné
    - prototype: Vec2d calculateAttractionForce(const Vec2d& targetPosition) const;

- mise à jour position, vitesse, direction:
    - arguments nécessaires:
        - la force d'attraction
        - le temps écoulé
    - type de retour: void
    - prototype: void updateMotion(const Vec2d& attractionForce, sf::Time dt) const;
*************************************************
##Q2.6
Utilisation d'un type énuméré de la manière suivante: on utilise un enum "DecelerationMode" qu'on déclare dans le dossier Collider.hpp car l'enum sera utilisé par ChasingAutomaton et Animal qui héritent tous les deux de Collider. Ensuite, pour pouvoir modifier le mode de décélération à partir de l'extérieur, on crée un setter qu'on met en méthode publique. On crée un attribut de type DeclarationMode qu'on initialise par défaut à Medium qui correspond à une décélération de 0.6. 
**************************************************************************************************
##Q2.7
Cela permet tout d'abord d'empêcher une modification extérieure qui pourrait notamment mener à des soucis comme l'absence de programme clamping pour un set position et donc une sortie du monde torique. Cela permet aussi d'empêcher une rotation impossible qui reviendrait à mettre des valeurs supérieures à 1 ou inférieures à -1. Cela permet tout de même que les descendants de ces classes puissent utiliser ces méthodes puisque les animaux spécifiques des sous-classes auront besoin de modifier leurs rotation en fonction de leurs comportements divers.
**************************************************************************************************
##Q2.8
On doit ajouter à l'intérieur du cpp de la classe Environment à l'intérieur de la méthode draw une boucle for qui prend l'ensemble des animaux 'faune' qui est un ensemble de pointeurs sur les animaux et appelle la fonction Animal::draw sur l'ensemble de ces animaux pour les afficher avec leur champ de vision (affichés avec la méthode drawVision appelée par Animal::draw). 
**************************************************************************************************
##Q2.9
C'est parce que la méthode setRotation() est protected et pour pouvoir y accéder il faut être un descendant d'un animal ou un animal d'où l'intérêt de créer la sous-classe DummyAnimal qui par l'héritage peut accéder à setRotation() et qui pourra alors modifier la direction de l'animal pour les besoins du test. On ne peut pas y accéder de l'extérieur. 
**************************************************************************************************
##Q2.10
On propose un tableau dynamique de Vec2d comme type de retour car on peut accéder à la position des cibles qui sont situées dans le champ de vision de l'animal.
**************************************************************************************************
##Q2.11
Il faut qu'on change la fonction Environment::update(sf::Time dt) de manière à ce qu'elle parcourt l'ensemble des animaux et qu'il mette à jour le mouvement de l'ensemble des animaux en faisant appel pour chaque animal à Animal::update(sf::Time dt).
*************************************************
##Q3.1
Nous avons déclaré comme méthodes virtuelles pures: getStandardMaxSpeed() const, getMass() const, getViewRange() const, getViewDistance() const, getRandomWalkRadius() const, getRandomWalkDistance() const, getRandomWalkJitter() const.
Ces méthodes dépendent des caractéristiques spécifiques à chaque animal et ne peuvent donc pas être définies de manière générique au niveau abstrait de Animal. On utilise override dans les classes Lizard et Scorpion pour chacune des méthodes ci-dessus, afin d'assurer une correspondance explicite avec la méthode virtuelle de la classe Animal.
*************************************************
##Q3.2
On doit pour cela changer la valeur de "initial" dans la section "Energy" de Json et la remplacer par la nouvelle valeur souhaitée et on enregistre le fichier. On appuie sur "C" pour changer les paramètres au cours de la simulation après avoir effectué ce changement. 
*************************************************
##Q3.3
Si l'on garde le type de retour en modifiant la méthode getTargetInSightForAnimal en getEntityInSightForAnimal on retrouverait avec des limitations dans la gestion de ces nouvelles entités “vus” par l'entité en question notamment si on prend en compte les comportements des animaux diffèrent.
A notre avis, pour obtenir un niveau satisfaisant d’encapsulation, la meilleure solution est d'établir le type de retour de cette méthode comme une liste de pointeurs sur les entités qui satisfassent les critères pour être considérés comme vus avec par ex TargetInSight. 
*************************************************
##Q3.4
On propose de faire hériter les classes Collider, Environment et Cloud Generator d'Updatable. En effet, de cette façon toutes les classes qui héritent de Collider, qui possèdent une fonction update, hériteront de cette classe. On procède de même pour la classe Drawable dont hériteront Collider et Environment (pas CloudGenerator puisque cette classe ne possède pas de fonction draw.
*************************************************
##Q3.5
Tester les types à l'exécution casse le polymorphisme de la conception et rend le code fragile et difficile à maintenir dans le futur. Utiliser le double dispatch est beaucoup mieux parce qu’il s’agit d’une solution qui résout le problème en manière indirecte grâce à la surcharge des méthodes “eatable” et “eatableDispatch” .
*************************************************
##Q3.6
Seuls les animaux affichent les informations de debugging donc il est intéressant de les placer au niveau de la classe Animal.
On avait déjà mis Collider en Drawable puisque toutes les classes qui héritent de Collider sont dessinables. 
*************************************************
##Q3.7
On crée une méthode virtuelle getEntityMaxAge() dans la classe OrganicEntity qui retourne par défaut 10E9 comme spécifié dans l'énoncé si la méthode n'est pas redéfinie dans la sous-classe correspondant à l'entité en question. Pour les entités pour lesquelles on veut une valeur de retour spécifique pour la longévité on redéfinit getEntityMaxAge().
*************************************************
##Q3.8
On marque les entités mortes (isDead() = true) en les remplaçant par nullptr après avoir appliqué un delete (empêcher fuite de mémoire). On met le destructeur de OrganicEntity en méthode virtuelle pour que la suppression des entités des sous-classes se fasse proprement. 
Dans le Environment::update(sf::Time dt), avec la tournure proposée dans l'énoncé on retire tous les nullptr du vecteur pour qu’il ne contienne plus que des entités vivantes. C’est nécessaire car on ne peut pas modifier la taille d’une liste pendant qu’on le parcours dans une boucle for (Segmentation fault). 
*************************************************
##Q3.9
Avec un if qui contrôle si le niveau d'énergie a dépassé le seuil (nous avons mis le 25% de l'énergie initiale) on peut décider si la vitesse obtenue selon l'état de l’animal (dans le switch) doit être encore diminuée (ici réduite à un tiers de son valeur après le switch).
*************************************************
##Q3.10  
On crée une méthode virtuelle pure dans la classe OrganicEntity setEatenEnergy(). Les sous-classes Cactus et Lizard redéfinissent cette perte d'énergie à leur manière. On met une méthode vide pour redéfinir setEatenEnergy() dans scorpion car un scorpion ne peut pas être mangé. 
*************************************************
##Q3.11
Au lieu d’hériter de collider les OrganicEntity pourraient avoir Collider en attribut privé ce qui permettrait de gagner plus de liberté sur la modification des collider sans autant impacter les OrganicEntity que si elles en héritent. On perdrait cependant l’architecture actuelle de notre code avec des appels de fonctions comme isColliding(...), …
*************************************************
##Q3.12
On définit la méthode meet en déclarant comme virtuelle pure dans OrganicEntity et en déclarant pour chaque interaction possible de *this une méthode meetDispatch, d'abord comme virtuelle pure dans OrganicEntity. Puis, pour chaque entité organique on définit les méthodes meetDispatch qui définissent les intéractions que les entités organiques pourront avoir avec une autre entité. La méthode meet van appeler la méthode meetWith qui va gérer la rencontre entre le *this et l'entité organique passé en paramètre de cette fonction. On passera l'argument par pointeur non constant car on doit pouvoir modifier certains attributs à travers la fonction meetDispatch. 
*************************************************
##Q3.13
On crée un booléen isGestating qui devient true après l'accouplement. On crée un attribut gestating_counter incrémenté dans le update tant que le temps de gestating_counter est inférieur au temps de gestation qui est dans le main. Tant que le compteur est incrémenté, le booléen isGestating est true et l'animal reste en WANDERING. Une fois que le temps de gestation est dépassé, le booléen isDelivering devient true et isGestating devient false, ce qui modélise l'accouplement.
*************************************************
##Q3.14  
Dans Animal, on crée une méthode virtuelle pure void give_birth() qui est redéfini dans les sous-classes et qui ajoute une entité de l’espèce voulue dans l’environnement en appelant en l’occurrence addEntity dans Scorpion ajoute un nouveau scorpion. 
*************************************************
##Q3.15
Le nombre de bébés attendus est stocké dans un attribut entier privé nb_babies de Animal. Il est initialisé lors de l’accouplement et utilisé à la fin de la gestation pour faire spawn le nombre de bébés définis.
*************************************************
##Q3.16
Stocker un ensemble de prédateurs connus pour chaque animal peut être une bonne façon d'implémenter les mécanismes de fuite. Par contre dans notre conception nous avons préféré utiliser directement les booléens du eatableDispatch (pour comprendre, par exemple, si un scorpion peut manger un lézard) et distinguer avec ces contraintes les entités à traiter comme prédateurs par chaque animal.
*************************************************
##Q4.1         
Puisque Wave est un collider, elle héritera de la classe Collider, laquelle hérite déjà de Drawable et Updatable.
*************************************************
##Q4.2        
Avec un attribut compteur elapsed_time initialisé à 0 par le constructeur lorsqu’une wave est créé et mis à jour dans la méthode update qui s’occupe aussi d'utiliser cet attribut pour calculer le changement de rayon.
*************************************************
##Q4.3
Créer un attribut d’Environment qui stocke toutes les ondes (analogue aux listes “entities”, “clouds”, ..). Donc itérer sur cette liste lorsqu’on veut afficher ou effacer les ondes. 
*************************************************
##Q4.4        
Créer un autre attribut: une liste de pointeurs sur les obstacles présents dans la simulation. L'itération sur cette liste permet de mettre en place la fragmentation des ondes et l’effacement des rochers en faisant d’abord une boucle sur les waves puis sur chaque obstacle pour voir si le wave donné est en collision avec lui.
*************************************************
##Q4.5
On propose de le représenter avec un array qui est un static constexpr car il est le même pour tous les NeuronalScorpions contenant 8 paires constituées d'un Sensor représentant le senseur et d'un double représentant sa position et donc son angle en degré. On opte pour ce choix car le nombre de senseurs et leur position à l'avance et ce nombre ne change pas au cours du temps. On crée également une constante globale qui est un array de 8 double représentant les 8 positions possibles pour les senseurs. On opte pour ce choix car il s'agit d'une constante tout au long du programme. Pour construire le NeuronalScorpion, doit utiliser une boucle for en initialisant chaque senseur avec un senseur par défaut et la position appropriée à son index. On ne pourrait pas initialiser le array de sensor directement. 
*************************************************
##Q4.6
Le prototype est Vec2d getPositionOfSensor(size_t chosen_sensor) const puisqu'il s'agit d'une fonction qui doit renvoyer la position (Vec2d) d'un senseur donné (chosen_sensor). On utilise size_t car les senseurs ont un sensorIndex strictement positif et on peut accéder à l'angle des différents senseurs contenus dans l'enum SENSOR_POSITIONS grâce à leur index.
*************************************************
##Q4.7
On ajoute une fonction de prototype double Environment::getIntensitySumAt(const Vec2d& location) const dans la classe Environment pour calculer l'intensité cumulée des ondes qui la touchent. On ajoute dans la classe Wave un getter getArcs pour avoir accès aux arcs pour une vague donnée. Il n'y a pas besoin ainsi d'un getter trop intrusif pour avoir accès à l'ensemble des ondes car celui-ci est déjà contenu dans la classe Environment. On ajoute aussi une méthode bool isAngleInArc(double obstacle_angle, std::pair<double, double> arc) const qui est une méthode complémentaire servant à tester les condition de savoir si un objet se trouve dans un arc.
*************************************************
##Q4.8
On prédéclare la classe NeuronalScorpion pour chaque Sensor et on inclut dans ses attributs un pointeur au NeuronalScorpion auquel le senseur appartient. On stocke aussi l'index du senseur qu'on a ajouté dans ses attributs privés.
*************************************************
##Q4.9
Pour le constructeur du senseur on ajoute donc le scorpion auquel le senseur appartient et utilisant l'allocation dynamique à travers un new puisqu'on veut un pointeur sur le scorpion. On ajoute un pointeur sur un scorpion car au moment où on construit les senseurs le scorpion n'est pas encore entièrement construit (peut valoir nullptr). C'est le seul moyen de pouvoir utiliser un this dans le constructeur de Sensor. 


*************************************************
##Q4.10
Les états spécifiques au NeuronalScorpion on les ajoute que dans NeuronalScorpion car elles ne vont pas s'appliquer aux autres entités. En effet, par exemple un lézard ne pourra pas avoir un comportement comme notre NeuronalScorpion dans l'implémentation actuelle du code car il ne s'agit pas d'une caractéristique d'un lézard de pouvoir détecter ainsi une proie. C’est pourquoi on ne les ajoute pas dans Animal. On n'ajoute pas ces états dans Scorpion car seulement les NeuronalScorpions sont capables de réaliser ces traitements spécifiques. 
*************************************************
##Q4.11
Les horloges relatives à MOVING et à IDLE on les met dans Neuronal Scorpion car c'est seulement eux qui en auront besoin pour leur update. Je propose de les modéliser par des compteurs comme dans l'étape 3 (ex: sf::Time idle_time). Ces compteurs seront incrémentés à chaque pas de simulation. 
*************************************************
##Q4.12
Deux horloges sont utilisées pour gérer les transitions entre les états du NeuronalScorpion: les attributs idle_time et moving_time.
La variable idle_time est utilisée lorsque le scorpion est dans l’état IDLE. Elle s’incrémente à chaque mise à jour tant que le scorpion reste inactif. Si cette durée dépasse une valeur seuil définie, le scorpion quitte l’état IDLE pour entrer dans l’état WANDERING_. Inversement, si une activité sensorielle est détectée pendant l’état WANDERING_, le scorpion retourne à l’état IDLE et idle_time est alors réinitialisée.
Moving_time est utilisée dans l’état MOVING. Elle mesure la durée pendant laquelle le scorpion se déplace en réponse à une stimulation causée par une vague. Une fois que moving_time dépasse la limite définie, le scorpion interrompt son mouvement et retourne à l’état IDLE. À ce moment-là, moving_time et idle_time sont remises à zéro.
*************************************************
##Q5.1
Nous avons décidé d'utiliser des ordered maps. Il s'agit de tableaux de valeurs de deux types associés, dans notre cas les deux maps ont tous les deux une “clé” int associé soit à un pointeur sur un Graph pour l’ensemble des graphs, soit a une string pour l’ensemble des libellés.
*************************************************
##Q5.2
Nous créons une méthode virtuelle pure void incrementCounter() const dans OrganicEntity. Cette méthode va appeler de manière polymorphique une fonction d’incrémentation définie comme publique dans environnement qui permet d’incrémenter le compteur de chaque type d’espèces. Ainsi, dans le update de Environment avec la fonction void counterUpdate() on calcule le nombre d’entités de chaque espèces à chaque pas de simulation, d’où l’utilité de remettre les compteurs à 0 à chaque pas de simulation.
