import infoUtils

if __name__ == "__main__":

    distribution1 = infoUtils.getMatrixImg("lena.jpeg")
    distribution2 = infoUtils.getMatrixImg("lena4.jpeg")
    probaLena1 = infoUtils.getProbabilities(distribution1)
    probaLena4 = infoUtils.getProbabilities(distribution2)
    conjointeL1xL2 = infoUtils.conjointe(distribution1, distribution2)
    IMNL1xL2 = infoUtils.NMI(distribution1, distribution2)

    print(f"Entropy P1 = {infoUtils.entropy(probaLena1)}")
    print(f"Entropy P2 = {infoUtils.entropy(probaLena4)}")
    #print(f"conjointe P1xP2 = {conjointeL1xL2}")
    print(f"Entropy P1xP2 = {infoUtils.entropy(conjointeL1xL2)}")
    print(f"IMN L1xL2 = {IMNL1xL2}")
