#include <include/api.h>

void ProbeSystem(
    EcsRows *rows) 
{
    SysTestData *ctx = ecs_get_context(rows->world);
    if (!ctx) {
        return;
    }

    ctx->system = rows->system;
    ctx->offset = rows->offset;
    ctx->column_count = rows->column_count;
    ctx->param = rows->param;

    int i;
    for (i = 0; i < ctx->column_count; i ++) {
        ctx->c[ctx->invoked][i] = rows->components[i];
        ctx->s[ctx->invoked][i] = ecs_column_source(rows, i + 1);
    }

    EcsEntity *e = ecs_column(rows, EcsEntity, 0);
    for (i = rows->offset; i < (rows->offset + rows->limit); i ++) {
        ctx->e[i - rows->offset + ctx->count] = e[i];
    }

    ctx->invoked ++;

    ctx->count += rows->limit;
}