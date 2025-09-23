import os
import struct
import sys

PAK_SIGNATURE = b"PACK"
PATH_SIZE = 200

def write_pak(folder_path, pak_path, base_assets_dir):

    files = []
    # --- only files directly in this folder ---
    for item in os.listdir(folder_path):
        item_path = os.path.join(folder_path, item)
        if os.path.isfile(item_path):
            # Store path relative to the assets folder
            # rel_path = os.path.relpath(item_path, base_assets_dir).replace("\\", "/")
            rel_path = "assets/" + os.path.relpath(item_path, base_assets_dir).replace("\\", "/")
            files.append((rel_path, item_path))

    if not files:
        return  # no files → no PAK

    os.makedirs(os.path.dirname(pak_path), exist_ok=True)

    with open(pak_path, "wb") as pak:
        pak.write(PAK_SIGNATURE)
        pak.write(struct.pack("<II", 0, 0))  # directory_offset, directory_size

        file_infos = []

        # --- data section ---
        for rel_path, full_path in files:
            offset = pak.tell()
            with open(full_path, "rb") as f:
                data = f.read()
                pak.write(data)
            size = len(data)
            file_infos.append((rel_path, offset, size))
            # print(f"Added file: path: {rel_path}, Offset: {offset}, Size: {size}")

        # --- directory at the end ---
        directory_offset = pak.tell()
        for rel_path, offset, size in file_infos:
            encoded_path = rel_path.encode("utf-8")[:PATH_SIZE]
            encoded_path += b"\x00" * (PATH_SIZE - len(encoded_path))
            pak.write(encoded_path)
            pak.write(struct.pack("<II", offset, size))

        directory_size = pak.tell() - directory_offset

        # --- update header ---
        pak.seek(4)
        pak.write(struct.pack("<II", directory_offset, directory_size))

    # print(f"PAK '{pak_path}' created with {len(files)} files.\n")

def build_assets(asset_dir, build_dir):
    for root, dirs, _ in os.walk(asset_dir):
        for d in dirs:
            folder_path = os.path.join(root, d)
            pak_name = f"{d}.pak"
            rel_root = os.path.relpath(root, asset_dir).replace("\\", "/")
            pak_path = os.path.join(build_dir, rel_root, pak_name)
            write_pak(folder_path, pak_path, base_assets_dir=asset_dir)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        # print("Usage: BundleMaker.py <assets_folder> <build_tool_bin>")
        sys.exit(1)

    assets_dir = sys.argv[1]
    build_tool_bin = sys.argv[2]

    if not os.path.exists(assets_dir):
        print(f"Assets folder '{assets_dir}' does not exist!")
        sys.exit(1)

    build_assets(assets_dir, build_tool_bin)
