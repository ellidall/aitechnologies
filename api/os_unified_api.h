#ifndef OS_UNIFIED_API_H
#define OS_UNIFIED_API_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    OS_SUCCESS = 0,
    OS_ERROR_INVALID_PARAM = -1,
    OS_ERROR_AUTH_FAILED = -2,
    OS_ERROR_HARDWARE_FAULT = -3,
    OS_ERROR_NOT_ENOUGH_DATA = -4,
    OS_ERROR_TIMEOUT = -5
} os_status_t;

typedef enum {
    LANG_EN_US = 0,
    LANG_RU_RU = 1,
    LANG_NATIONAL_CUSTOM = 2
} os_lang_t;

typedef enum {
    EMOTION_NEUTRAL = 0,
    EMOTION_HAPPY = 1,
    EMOTION_SAD = 2,
    EMOTION_ANGRY = 3,
    EMOTION_FEAR = 4,
    EMOTION_STRESSED = 5
} os_emotion_t;

typedef struct {
    const uint8_t *data;
    size_t width;
    size_t height;
    uint32_t channels;
} os_image_t;

typedef struct {
    const int16_t *pcm_samples;
    size_t sample_count;
    uint32_t sample_rate;
} os_audio_t;

typedef struct {
    char user_id[64];
    float confidence;
} os_bio_identity_t;

typedef struct {
    const char *vcf_data;
    size_t data_len;
    uint32_t loci_markers_count;
} os_dna_sample_t;

os_status_t os_bio_identify_fingerprint(const os_image_t *fp_image, os_bio_identity_t *out_identity);
os_status_t os_bio_identify_face(const os_image_t *face_image, os_bio_identity_t *out_identity);
os_status_t os_bio_identify_iris(const os_image_t *eye_image, os_bio_identity_t *out_identity);
os_status_t os_bio_identify_voice_fixed(const os_audio_t *voice_clip, const char *passphrase, os_bio_identity_t *out_identity);
os_status_t os_bio_identify_voice_prompted(const os_audio_t *voice_clip, const char *prompt, os_bio_identity_t *out_identity);
os_status_t os_bio_identify_voice_dialog(const os_audio_t *dialog_stream, size_t duration_sec, os_bio_identity_t *out_identity);
os_status_t os_bio_identify_dna(const os_dna_sample_t *dna_sample, os_bio_identity_t *out_identity);

os_status_t os_voice_speech_to_text(const os_audio_t *audio, char *out_text, size_t max_len);
os_status_t os_voice_synthesize_en(const char *text, os_audio_t *out_audio);
os_status_t os_voice_synthesize_multilang(const char *text, os_lang_t lang, os_audio_t *out_audio);

os_status_t os_nlp_semantic_vector_match(const char *text, const char *local_db_path, float *out_similarity, char *out_closest_match, size_t max_len);
os_status_t os_nlp_domain_semantic_analysis(const char *text, const char *domain_tag, char *out_intent, float *out_relevance);

os_status_t os_emotion_detect_voice(const os_audio_t *audio, os_emotion_t *out_emotion, float *out_valence, float *out_arousal);
os_status_t os_emotion_detect_handwriting(const os_image_t *handwriting_image, os_emotion_t *out_emotion, float *out_stress_level);

#ifdef __cplusplus
}
#endif

#endif