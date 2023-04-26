import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py databasesPath.csv sequencesPath.txt")

    # TODO: Read database file into a variable
    cases = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for case in reader:
            cases.append(case)
    #print(cases)
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as fileSeq:
        readerSeq = fileSeq.read().rstrip()
    # print(readerSeq)

    # TODO: Find longest match of each STR in DNA sequence
    AGATC = longest_match(readerSeq, "AGATC")
    TTTTTTCT = longest_match(readerSeq, "TTTTTTCT")
    AATG = longest_match(readerSeq, "AATG")
    TCTAG = longest_match(readerSeq, "TCTAG")
    GATA = longest_match(readerSeq, "GATA")
    TATC = longest_match(readerSeq, "TATC")
    GAAA = longest_match(readerSeq, "GAAA")
    TCTG = longest_match(readerSeq, "TCTG")

    # TODO: Check database for matching profiles
    if "large" in sys.argv[1]:
        for case in cases:
            #print(case["name"])
            if int(case["AGATC"]) == AGATC and int(case["TATC"]) == TATC and int(case["AATG"]) == AATG and int(case["TTTTTTCT"]) == TTTTTTCT and int(case["TCTAG"]) == TCTAG and int(case["GATA"]) == GATA and int(case["GAAA"]) == GAAA and int(case["TCTG"]) == TCTG:
                print(case["name"])
                sys.exit(0)
    else:
        for case in cases:
            #print(case["name"])
            if int(case["AGATC"]) == AGATC and int(case["TATC"]) == TATC and int(case["AATG"]) == AATG:
                print(case["name"])
                sys.exit(0)
        

    print("No match")
    sys.exit(1)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
