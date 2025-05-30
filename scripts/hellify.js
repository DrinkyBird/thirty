for (let x = 0; x < world.width; x++)
for (let y = 0; y < world.depth; y++)
for (let z = 0; z < world.height; z++) {
    let block = world.get(x, y, z);
    switch (block) {
        case 2: block = 3; break; // grass -> dirt
        case 8: block = 10; break; // water -> lava
        case 9: block = 11; break; // ...ditto, but static
        case 12: block = 13; break;  // sand -> gravel
        case 18: block = 0; break; // kill all the leaves
        default: break;
    }
    world.set(x, y, z, block);
}
