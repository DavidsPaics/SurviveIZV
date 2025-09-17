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
    base_path = "helperScript/RLEEncodeMap"

    in_file = os.path.join(base_path, "in.txt")
    out_file = os.path.join(base_path, "out.game-map")
    notes_file = os.path.join(base_path, "notes.txt")

    # Read input
    with open(in_file, "r") as f:
        tokens = f.read().split()

    # First two tokens are width and height
    width, height = map(int, tokens[:2])
    spawnx, spawny = map(int, tokens[2:4])
    tiles = list(map(int, tokens[4:]))

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
        # First line: width height + encoded map
        f.write(f"{width} {height} {spawnx} {spawny} ")
        f.write(" ".join(f"{count} {tile}" for count, tile in encoded))
        f.write("\n\n")  # empty line after map data

        # Append unique tile lines (ignore ID 0)
        unique_ids = sorted(set(tiles))
        for tid in unique_ids:
            if tid != 0:
                f.write(f"{tid} 0 0\n")

        # Optional notes at the very end
        if notes:
            f.write("\n" + notes + "\n")


if __name__ == "__main__":
    main()
