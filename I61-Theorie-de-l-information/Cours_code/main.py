from math import log2

def get_proba_element(x_element_amount, total_element_amount) -> float:
    """
    Renvoie la probabilité de l'evenement "obtenir x"
    en supposant que la loi de probabilité est uniforme 
    """
    return x_element_amount / total_element_amount

def get_answer_cost(total_element_amount) -> float:
    """
    Renvoie le cout de la solution. (recherche dichotomique)
    """
    return log2(total_element_amount)

def get_hint_cost(x_element_amount, total_element_amount) -> float:
    """
    Renvoie le cout de l'information "je sais que l'element 
    recherché est un x parmis tous les elements"
    """
    return log2(total_element_amount / x_element_amount)

def get_information_quantity(x_element_amount, total_element_amount) -> float:
    """
    Renvoie la quantité d'information relative à 1 evenement
    """
    return log2(total_element_amount / x_element_amount)

def get_entropy(probabilities: list) -> float:
    """
    Calcul la valeur moyenne de l'information pour une ldp
    """
    sum = 0
    for proba in probabilities:
        if (proba != 0):
            sum += proba * log2(proba)
    return -sum

def get_entropy_max(total_element_amount) -> float:
    """
    Renvoie la valeur maximale de l'entropie
    C'est le cas lorsque toutes les proba sont les mêmes
    """
    return log2(total_element_amount)

def get_conjointe_proba(pair_occurences: list, total_element_count):
    """
    transforme la matrice de paire d'occurence
    en matrice de proba

    pair_occurences est une liste de liste
    """
    pair_proba = []
    for line in range(len(pair_occurences)):
        pair_proba_line = []
        for col in range(len(pair_occurences[line])):
            pair_proba_line.append(pair_occurences[line][col] / total_element_count)
        pair_proba.append(pair_proba_line)
    return pair_proba

def get_conjointe_entropy(pair_proba):
    """
    Calcul la quantité moyenne d'information dans la ldp
    """
    sum = 0
    for pair_proba_line in pair_proba:
        sum += get_entropy(pair_proba_line)
    return sum

def get_marginal_proba(pair_proba, variable_number):
    """
    Renvoie la liste des proba marginales pour la variable
    numero variable_number
    """
    if (variable_number == 1):
        probas_1 = []
        for line in range(len(pair_proba)):
            sum = 0
            for col in range(len(pair_proba[0])):
                sum += pair_proba[line][col]
            probas_1.append(sum)
        return probas_1
    elif (variable_number == 2):
        probas_2 = []
        for col in range(len(pair_proba[0])):
            sum = 0
            for line in range(len(pair_proba)):
                sum += pair_proba[line][col]
            probas_2.append(sum)
        return probas_2

def get_conjointe_ldp_dependency(pair_proba):
    """
    Renvoie un coef entre 0 et 1
    Proche de 1: faible dépendance
    Proche de 0: forte dépendance
    """
    X = get_marginal_proba(pair_proba, 1)
    Y = get_marginal_proba(pair_proba, 2)
    H_X = get_entropy(X)
    H_Y = get_entropy(Y)
    H_X_AND_Y = get_conjointe_entropy(pair_proba)

    return (H_X_AND_Y - H_Y) / H_X

def get_entropy_know_second_ldp(pair_proba) -> float:
    """
    Renvoie H(X|Y) l'entropie de X si on a déjà Y
    """
    H = get_marginal_proba(pair_proba, 1)
    return get_conjointe_entropy(pair_proba) - get_entropy(H)

def get_mutual_information(pair_proba):
    H_X = get_entropy(get_marginal_proba(pair_proba, 1))
    H_Y = get_entropy(get_marginal_proba(pair_proba, 2))
    H_X_AND_Y = get_conjointe_entropy(pair_proba)
    return H_X + H_Y - H_X_AND_Y

def get_mutual_information_fast(pair_proba):
    H_Y = get_entropy(get_marginal_proba(pair_proba, 2))
    # a faire

def get_divergence_of_kullbachLeibler(p_array, q_array):
    sum = 0
    for i in range(min(len(p_array), len(q_array))):
        sum += p_array[i] * log2(p_array[i] / q_array[i])
    return sum

def get_mutual_information_kullbackLeibler(pair_proba):
    X = get_marginal_proba(pair_proba, 1)
    Y = get_marginal_proba(pair_proba, 2)
    p_array = []
    q_array = []
    for line in range(len(pair_proba)):
        for col in range(len(pair_proba[0])):
            p_array.append(pair_proba[line][col])
            q_array.append(X[col] * Y[line])
    return get_divergence_of_kullbachLeibler(p_array, q_array)

def get_mutual_information_normalized(pair_proba):
    H_X = get_marginal_proba(pair_proba, 1)
    H_Y = get_marginal_proba(pair_proba, 2)
    return (2 * get_mutual_information(pair_proba)) / (H_X + H_Y)

if __name__ == "__main__":
    pair_proba = [
        [1/8,  1/16, 1/16, 1/4 ],
        [1/16, 1/8,  1/16, 0   ],
        [1/32, 1/32, 1/16, 0   ],
        [1/32, 1/32, 1/16, 0   ]
    ]
    print(get_conjointe_entropy(pair_proba))
    print(get_conjointe_ldp_dependency(pair_proba))


