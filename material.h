
class Material
{
    float reflectance;
    float coeff_ambientLight;
    float coeff_diffuseLight;
    float coeff_specularLight;
    public:
    
    Material(float reflectance=0,float coeff_ambientLight=0,float coeff_diffuseLight=0, float coeff_specularLight=0)
    {
        this->reflectance = reflectance;
        this-> coeff_ambientLight = coeff_ambientLight;
        this-> coeff_diffuseLight = coeff_diffuseLight;
        this-> coeff_specularLight = coeff_specularLight;
    }
    float getReflectance()
    {
        return reflectance;
    }
    float getAmbientCoeff()
    {
        return coeff_ambientLight;
    }
    float getDiffuseCoeff()
    {
        return coeff_diffuseLight;
    }
    float getSpecualrCoeff()
    {
        return coeff_specularLight;
    }
};