for (let x = 0; x < world.width; x++)
for (let y = 0; y < world.depth; y++)
for (let z = 0; z < world.height; z++) {
    const block = world.get(x, y, z);
    // wood or leaves
    if (block == 17 || block == 18) {
        world.set(x, y, z, 0);
    }
}
