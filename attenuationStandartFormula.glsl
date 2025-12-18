fragPos - pos of a model;
lightStructures[i].mPos - pos of a source of light;

float distance = length(fragPos - lightStructures[i].mPos);
float attenuation = 1.0f / (1.0f + 0.09f * distance + 0.032f * distance * distance);
result *= attenuation;
