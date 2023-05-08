import info_utils
from coding_table import CodingTable
from com_system import ComSystem

if __name__ == "__main__":
    # Calcul de l'entropie de la langue française
    table = info_utils.get_french_table()
    print(f"Entropy of french table = {info_utils.entropy(table)}")

    # Test de la génération d'une table à partir d'un texte
    all_text = "BBBBBBBBBBBA"
    table = info_utils.generate_table(all_text)
    print(f"Entropy of the all_text = {info_utils.entropy(table)}")
    text = "BBBBAAAAAAB"
    print(f"Auto-info from text \"{text}\" = {info_utils.auto_info_word(text, table)}")

    # Encodage de la source
    morse_dict = {
        "A": ".-", "G": "--.", "M": "--", "S": "...", "Y": "-.--",
        "B": "-...", "H": "....", "N": "-.", "T": "-", "Z": "--..",
        "C": "-.-.", "I": "..", "O": "---", "U": "..-",
        "D": "-..", "J": ".---", "P": ".--.", "V": "...-",
        "E": ".", "K": "-.-", "Q": "--.-", "W": ".--",
        "F": "..-.", "L": ".-..", "R": ".-.", "X": "-..-",
    }
    table = info_utils.get_french_table()
    coding_table = CodingTable(morse_dict, info_utils.get_morse_alphabet())
    coding_table.register_proba_table(table)
    print(f"Average size of encoding char = {coding_table.get_average_traduction_size()}")

    com_system = ComSystem(coding_table)
    print(f"The systeme will able to transfer french to morse: {com_system.can_transfer()}")

    # Exercice du cours
    
    # Données
    table = {'A': 0.8, 'B': 0.15, 'C': 0.05}
    coding_translation = {'A': "0", 'B': "1", 'C': "01"}
    flow_source = 100.0
    coding_alphabet = ('0', '1')
    channel_source_flow = 95.0

    # Preparation
    coding_table = CodingTable(coding_translation, coding_alphabet)
    coding_table.register_proba_table(table)
    com_system = ComSystem(coding_table)
    com_system.register_source_flow(flow_source)
    com_system.register_channel_source_flow(channel_source_flow)

    # Question 1
    for c in table.keys():
        print(f"The auto info of char \"{c}\" = {info_utils.auto_info_char(c, table)}")

    # Question 2
    print(f"The entropy of source = {info_utils.entropy(table)}")
    
    # Question 3
    print(f"The flow source = {flow_source}")

    # Question 4
    print(f"Source emission = {com_system.get_emission_rate_source()}")

    # Question 5
    print(f"Channel source flow = {channel_source_flow}")

    # Question 6
    print(f"Capacity of the channel = {com_system.get_channel_source_capacity()}")

    # Question 7 & 8
    print(f"Can transfer info = {com_system.can_transfer()}")