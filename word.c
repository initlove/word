#include <stdio.h>
#include <string.h>
#include <glib.h>

static GHashTable *database = NULL;

gboolean
is_space (gchar *str)
{
    int i;

    if (strlen (str) < 1)
        return TRUE;
    for (i = 0; *(str + i); i++) {
        if (!g_ascii_isspace (*(str + i)))
            return FALSE;
    }
    return TRUE;
}

GHashTable *
init_database (gchar *file)
{
    GError *error = NULL;
    gint len, i;
    gchar *content;
    gchar **array;

    if (!g_file_get_contents (file, &content, &len, &error)) {
        printf ("Error get : %s\n", error->message);
        g_error_free (error);
        return NULL;
    }
    database = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);
    array = g_strsplit (content, "\n", -1);

    gchar *key = NULL;
    gchar *value = NULL;

    for (i = 0; array [i]; i++) {
        if (i % 3 == 0) {
            gchar *p;
            p = strchr (array[i], ' ');
            if (p)
                *p = NULL;
            key = array[i];
        } else if (i % 3 == 1) {
            value = array [i];
        } else {
            g_hash_table_insert (database, g_strdup (key), g_strdup (value));
            key = NULL;
            value = NULL;
        }
    }
    
    g_free (content);
    g_strfreev (array);

    return database;
}

void
look_pre (gchar *key,
            gchar *value, 
            gchar *data)
{
    if (strstr (key, data))
        printf ("key got %s -- value got %s\n", key, value);
}

int main ()
{
    gchar *file = "./mba5500";
    GHashTable *hash;

    hash = init_database (file);

    gchar *key = "resp";
    printf ("look up %s\n", g_hash_table_lookup (hash, key));

    g_hash_table_foreach (hash, look_pre, "re");
    return 0;
}


