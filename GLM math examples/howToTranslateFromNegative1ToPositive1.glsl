vec3 normal = texture(uniformNormalMap, texCoord).rgb; // in range (0.0f, 1.0f);
normal = normalize(normal * 2.0f - 1.0f); // translates into range of (-1.0f, 1.0f);
normal = normalize(normal * 0.5 + 0.5f); // translates into range of (0.0f, 1.0f);
