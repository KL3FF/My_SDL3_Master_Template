import os
import struct
import sys

def build_bundle(base_folder, bundle_file_path):
    files = []

    # --- 1. Recursively collect all files ---
    for root, _, filenames in os.walk(base_folder):
        for fname in filenames:
            full_path = os.path.join(root, fname)
            rel_path = os.path.relpath(full_path, base_folder)
            files.append((rel_path.replace("\\", "/"), full_path))

    # --- 2. Ensure target directory exists ---
    bundle_dir = os.path.dirname(bundle_file_path)
    os.makedirs(bundle_dir, exist_ok=True)

    # --- 3. Write bundle ---
    with open(bundle_file_path, "wb") as bundle:
        bundle.write(struct.pack("<I", len(files)))
        dir_pos = bundle.tell()
        for _ in files:
            bundle.write(b"\x00" * 208)

        file_infos = []
        for rel_path, full_path in files:
            offset = bundle.tell()
            with open(full_path, "rb") as f:
                data = f.read()
                bundle.write(data)
            size = len(data)
            file_infos.append((rel_path, offset, size))

        bundle.seek(dir_pos)
        for rel_path, offset, size in file_infos:
            encoded_path = rel_path.encode("utf-8")[:200]
            encoded_path += b"\x00" * (200 - len(encoded_path))
            bundle.write(encoded_path)
            bundle.write(struct.pack("<II", offset, size))

    print(f"Bundle '{bundle_file_path}' created with {len(files)} files.")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: BundleMaker.py <assets_folder> <bundle_file>")
    else:
        build_bundle(sys.argv[1], sys.argv[2])
