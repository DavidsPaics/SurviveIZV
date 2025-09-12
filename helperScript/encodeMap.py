import os

def rle_encode(data):
    """Run-length encode a list of integers."""
    encoded = []
    if not data:
        return encoded

    count = 1
    prev = data[0]

    for val in data[1:]:
        if val == prev:
            count += 1
        else:
            encoded.append((count, prev))
            count = 1
            prev = val
    encoded.append((count, prev))  # last run
    return encoded


def main():
    base_path = "helperScript"

    in_file = os.path.join(base_path, "in.txt")
    out_file = os.path.join(base_path, "out.game-map")
    notes_file = os.path.join(base_path, "notes.txt")

    # Read input
    with open(in_file, "r") as f:
        tokens = f.read().split()

    # First two tokens are width and height
    width, height = map(int, tokens[:2])
    tiles = list(map(int, tokens[2:]))

    if len(tiles) != width * height:
        print(f"Warning: expected {width*height} tiles, got {len(tiles)}")

    # RLE encode
    encoded = rle_encode(tiles)

    # Read notes
    notes = ""
    if os.path.exists(notes_file):
        with open(notes_file, "r") as f:
            notes = f.read().strip()

    # Write output
    with open(out_file, "w") as f:
        f.write(f"{width} {height} ")
        f.write(" ".join(f"{count} {tile}" for count, tile in encoded))
        f.write("\n\n10000 0 <- prevent interpreting notes as data\n")
        if notes:
            f.write(notes + "\n")


if __name__ == "__main__":
    main()
