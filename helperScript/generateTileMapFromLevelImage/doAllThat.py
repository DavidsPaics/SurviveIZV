# helperScript/generateTileMapFromLevelImage/script.py

from PIL import Image
import numpy as np
import os

TILE_SIZE = 32

def is_black_or_transparent(tile):
    """Return True if tile is fully black or fully transparent"""
    arr = np.array(tile)
    rgb = arr[:, :, :3]
    alpha = arr[:, :, 3]
    return np.all(rgb == 0) or np.all(alpha == 0)

def tile_equal(t1, t2):
    """Check if two tiles are pixel-perfect equal"""
    return np.array_equal(np.array(t1), np.array(t2))

def load_existing_tiles(path):
    """Load existing-tilemap.png as list of tiles (in one row)"""
    img = Image.open(path).convert("RGBA")
    w, h = img.size
    tiles = []
    for x in range(0, w, TILE_SIZE):
        tile = img.crop((x, 0, x + TILE_SIZE, TILE_SIZE))
        tiles.append(tile)
    return tiles, img

def save_tilemap(existing_img, new_tiles, out_path):
    """Append new tiles to existing image and save"""
    if existing_img:
        ex_w, ex_h = existing_img.size
    else:
        ex_w, ex_h = 0, TILE_SIZE

    new_w = ex_w + len(new_tiles) * TILE_SIZE
    result = Image.new("RGBA", (new_w, TILE_SIZE))

    if existing_img:
        result.paste(existing_img, (0, 0))

    for i, t in enumerate(new_tiles):
        result.paste(t, (ex_w + i * TILE_SIZE, 0))

    result.save(out_path)

def main():
    base_path = os.path.dirname(os.path.abspath(__file__))

    # File paths inside same folder
    level_path = os.path.join(base_path, "level.png")
    existing_tilemap_path = os.path.join(base_path, "existing-tilemap.png")
    updated_tilemap_path = os.path.join(base_path, "updated-tilemap.png")
    map_output_path = os.path.join(base_path, "level.game-map")

    # Load images
    level = Image.open(level_path).convert("RGBA")

    if os.path.exists(existing_tilemap_path):
        existing_tiles, existing_img = load_existing_tiles(existing_tilemap_path)
    else:
        existing_tiles, existing_img = [], None

    # Unique tiles dictionary (IDs start at 1)
    unique_tiles = {i + 1: t for i, t in enumerate(existing_tiles)}

    width, height = level.size
    grid_w = width // TILE_SIZE
    grid_h = height // TILE_SIZE

    map_data = []

    for gy in range(grid_h):
        row = []
        for gx in range(grid_w):
            tile = level.crop((
                gx * TILE_SIZE,
                gy * TILE_SIZE,
                (gx + 1) * TILE_SIZE,
                (gy + 1) * TILE_SIZE
            ))

            # Empty tile → ID 0
            if is_black_or_transparent(tile):
                row.append(0)
                continue

            # Check if tile already exists
            found_id = None
            for tid, ut in unique_tiles.items():
                if tile_equal(tile, ut):
                    found_id = tid
                    break

            if found_id is None:
                new_id = len(unique_tiles) + 1
                unique_tiles[new_id] = tile
                found_id = new_id

            row.append(found_id)
        map_data.append(row)

    # Save updated tilemap
    new_tiles = [unique_tiles[i] for i in range(len(existing_tiles) + 1, len(unique_tiles) + 1)]
    save_tilemap(existing_img, new_tiles, updated_tilemap_path)

    # Save level.game-map
    with open(map_output_path, "w") as f:
        f.write(f"{grid_w} {grid_h}\n0 0\n")
        for row in map_data:
            f.write(" ".join(map(str, row)) + "\n")

    print("✅ updated-tilemap.png and level.game-map generated!")

if __name__ == "__main__":
    main()
