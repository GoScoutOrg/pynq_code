#include <microhttpd.h>
#include <stdio.h>

#define PORT 8080

static int handle_request(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method, const char *version,
                          const char *upload_data, size_t *upload_data_size, void **con_cls)
{
    const char *page = "<html><head><title>System Status</title><style>body{font-family:sans-serif;margin:0;padding:0;background-color:#F4F4F4;}.container{max-width:1200px;margin:0 auto;padding:20px;background-color:#FFFFFF;box-shadow:0px 0px 20px #CCCCCC;}.system{display:inline-block;width:200px;height:200px;margin:20px;background-color:#FFFFFF;border:1px solid #CCCCCC;border-radius:10px;box-shadow:0px 0px 10px #CCCCCC;text-align:center;}.system .name{font-size:24px;font-weight:bold;margin-top:20px;margin-bottom:10px;}.system .status{font-size:18px;font-weight:bold;margin-bottom:10px;}.system .details{font-size:14px;}.status-ok{color:green;}.status-warning{color:orange;}.status-error{color:red;}</style></head><body><div class=\"container\"><h1>System Status</h1><div class=\"system\"><div class=\"name\">System 1</div><div class=\"status status-ok\">Operational</div><div class=\"details\">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer in ex augue. Donec quis lectus sit amet nulla pulvinar malesuada.</div></div><div class=\"system\"><div class=\"name\">System 2</div><div class=\"status status-warning\">Degraded</div><div class=\"details\">Nulla facilisi. Nullam in mauris ac ipsum gravida pharetra vel eu tellus. Fusce ut dolor elit.</div></div><div class=\"system\"><div class=\"name\">System 3</div><div class=\"status status-error\">Critical</div><div class=\"details\">Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Sed id odio eleifend, ultricies elit non, tempus purus.</div></div></div></body></html>";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main(int argc, char **argv)
{
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &handle_request, NULL, MHD_OPTION_END);
    if (daemon == NULL) {
        printf("Error: Failed to start MHD daemon\n");
        return 1;
    }
    printf("Web server listening on port %d...\n", PORT);
    getchar(); // Wait for a keypress to stop the server
    MHD_stop_daemon(daemon);
    return 0;
}