#ifndef SIZE_MAX
#define SIZE_MAX (~(size_t)0)
#endif

typedef int type_el; /* pour définir le type d'un élément */
typedef struct {
	size_t size;      /* nombre d'éléments dans le tableau */
	size_t allocated; /* taille effectivement allouée */
	type_el* content; /* tableau de contenu (alloc. dyn.) */
} vector;


vector* vector_construct(vector* v) {
	vector* result = v;
	if (result != NULL) {
		result->content = calloc(VECTOR_PADDING,
		sizeof(type_el));
		if (result->content != NULL) {
			result->size = 0;
			result->allocated = VECTOR_PADDING;
		} else {
			/* retourne NULL si on n'a pas pu allouer la chaîne */
			result = NULL;
		}
	}
	return result;
}

void vector_delete(vector* v) {
	if ((v != NULL) && (v->content != NULL)) {
		free(v->content);
		v->content = NULL;
		v->size = 0;
		v->allocated = 0;
	}
}

size_t vector_push(vector* vect, type_el val) {
	if (vect != NULL) {
		while (vect->size >= vect->allocated) {
			if (vector_enlarge(vect) == NULL) {
				return 0;
			}
		}
		vect->content[vect->size] = val;
		++(vect->size);
		return vect->size;
	}
	return 0;
}

vector* vector_enlarge(vector* v) {
	vector* result = v;
	if (result != NULL) {
		type_el* const old_content = result->content;
		result->allocated += VECTOR_PADDING;
		if ((result->allocated > SIZE_MAX / sizeof(type_el)) ||
		((result->content = realloc(result->content, result->allocated * sizeof(type_el))) == NULL)) {
			result->content = old_content;
			result->allocated -= VECTOR_PADDING;
			result = NULL;
		}
	}
	return result;
}
