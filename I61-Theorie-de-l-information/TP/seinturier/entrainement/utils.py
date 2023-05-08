from typing import Dict

def create_reverse_dict(d:Dict[str,str]) -> Dict[str,str]:
    new_dict = {}
    for key,value in d.items():
        new_dict[value] = key
    return new_dict