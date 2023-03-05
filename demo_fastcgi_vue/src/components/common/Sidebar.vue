<template>
    <div class="sidebar">
        <el-menu
            class="sidebar-el-menu"
            :default-active="onRoutes"
            :collapse="collapse"
            background-color="#324157"
            text-color="#bfcbd9"
            active-text-color="#20a0ff"
            unique-opened
            router
        >
            <div>
                <template v-for="item in Items">
                    <template v-if="item.subs">
                        <el-submenu :index="item.index" :key="item.index">
                            <template slot="title">
                                <i :class="item.icon"></i>
                                <span slot="title">{{ item.title }}</span>
                            </template>
                            <template v-for="subItem in item.subs">
                                <el-submenu v-if="subItem.subs" :index="subItem.index" :key="subItem.index">
                                    <template slot="title">{{ subItem.title }}</template>
                                    <el-menu-item v-for="(threeItem, i) in subItem.subs" :key="i" :index="threeItem.index">{{
                                        threeItem.title
                                    }}</el-menu-item>
                                </el-submenu>
                                <el-menu-item v-else :index="subItem.index" :key="subItem.index">{{ subItem.title }}</el-menu-item>
                            </template>
                        </el-submenu>
                    </template>
                    <template v-else>
                        <el-menu-item :index="item.index" :key="item.index">
                            <i :class="item.icon"></i>
                            <span slot="title">{{ item.title }}</span>
                        </el-menu-item>
                    </template>
                </template>
            </div>
        </el-menu>
    </div>
</template>

<script>
import bus from '../common/bus';
export default {
    data() {
        return {
            collapse: false,
            roseID: this.$store.getters.getUser.roseID,
            Items: [],
            studentsItems: [
                {
                    icon: 'el-icon-lx-home',
                    index: 'dashboard',
                    title: '系统首页'
                },
                {
                    icon: 'el-icon-user',
                    index: 'admin',
                    title: '用户信息管理',
                    subs: [
                        {
                            index: 'personInfo',
                            title: '个人信息'
                        }
                    ]
                },
                {
                    icon: 'el-icon-picture',
                    index: '4',
                    title: '人脸库管理',
                    subs: [
                        {
                            index: 'UploadFace',
                            title: '上传人脸'
                        },
                        {
                            index: 'UpdateFace',
                            title: '更新人脸'
                        },
                        {
                            index: 'personInfo',
                            title: '人脸信息'
                        }
                    ]
                },
                {
                    icon: 'el-icon-camera-solid',
                    index: 'photograph',
                    title: '图片拍照'
                },
                {
                    icon: 'el-icon-reading',
                    index: 'courses',
                    title: '课程表',
                    title: '课程管理',
                    subs: [
                        {
                            index: 'courses',
                            title: '课程表'
                        },
                        {
                            index: 'personInfo',
                            title: '人脸信息'
                        }
                    ]
                },
                {
                    icon: 'el-icon-edit-outline',
                    index: 'records',
                    title: '考勤管理',
                    subs: [
                        {
                            index: 'stuAttendenceRecords',
                            title: '考勤记录'
                        },
                        {
                            index: 'recentAttendence',
                            title: '课程签到情况'
                        },
                        // {
                        //     index: 'webSocket',
                        //     title: 'webSocket'
                        // }
                    ]
                },

                {
                    icon: 'el-icon-s-tools',
                    index: 'account',
                    title: '账户安全设置',
                    subs: [
                        {
                            index: 'changePwd',
                            title: '修改密码'
                        },
                        {
                            index: 'changePwdN',
                            title: '密保设置'
                        },
                        {
                            index: 'accountStatus',
                            title: '账户冻结'
                        }
                    ]
                }
            ],

            teachersItems: [
                {
                    icon: 'el-icon-lx-home',
                    index: 'dashboard',
                    title: '系统首页'
                },
                {
                    icon: 'el-icon-user',
                    index: 'admin',
                    title: '用户信息管理',
                    subs: [
                        {
                            index: 'personInfo',
                            title: '个人信息'
                        }
                    ]
                },
                {
                    icon: 'el-icon-picture',
                    index: '4',
                    title: '人脸库管理',
                    subs: [
                        {
                            index: 'UploadFace',
                            title: '上传人脸'
                        },
                        {
                            index: 'UpdateFace',
                            title: '更新人脸'
                        },
                        {
                            index: 'personInfo',
                            title: '人脸信息'
                        }
                    ]
                },
                {
                    icon: 'el-icon-camera-solid',
                    index: 'photograph',
                    title: '图片拍照'
                },
                {
                    icon: 'el-icon-reading',
                    index: 'courses',
                    title: '课程管理',
                    subs: [
                        {
                            index: 'addcourse',
                            title: '添加课程'
                        },
                        {
                            index: 'courses',
                            title: '课程表'
                        },
                        {
                            index: 'arrangeCourse',
                            title: '安排课程'
                        },
                        {
                            index: 'studenttable',
                            title: '选课情况'
                        },
                        {
                            index: 'personInfo',
                            title: '人脸信息'
                        }
                    ]
                },
                {
                    icon: 'el-icon-edit-outline',
                    index: 'records',
                    title: '考勤管理',
                    subs: [
                        {
                            index: 'attendenceCourse',
                            title: '考勤课程'
                        },
                        {
                            index: 'recentAttendence',
                            title: '课程签到情况'
                        },
                        {
                            index: 'attendenceRecords',
                            title: '考勤记录'
                        }
                    ]
                },
                {
                    icon: 'el-icon-s-tools',
                    index: 'account',
                    title: '账户安全设置',
                    subs: [
                        {
                            index: 'changePwd',
                            title: '修改密码'
                        },
                        {
                            index: 'changePwdN',
                            title: '密保设置'
                        },
                        {
                            index: 'accountStatus',
                            title: '账户冻结'
                        }
                    ]
                }
            ],

            adminItems: [
                {
                    icon: 'el-icon-lx-home',
                    index: 'dashboard',
                    title: '系统首页'
                },
                // {
                //     icon: 'el-icon-lx-cascades',
                //     index: 'table',
                //     title: '基础表格'
                // },
                {
                    icon: 'el-icon-user',
                    index: 'admin',
                    title: '用户信息管理',
                    subs: [
                        {
                            index: 'students',
                            title: '学生信息管理'
                        },

                        {
                            index: 'teachers',
                            title: '教师信息管理'
                        },
                        {
                            index: 'personInfo',
                            title: '管理员个人信息'
                        }
                    ]
                },
                // {
                //     icon: 'el-icon-lx-copy',
                //     index: 'tabs',
                //     title: 'tab选项卡'
                // },
                // {
                //     icon: 'el-icon-lx-calendar',
                //     index: '3',
                //     title: '表单相关',
                //     subs: [
                //         {
                //             index: 'form',
                //             title: '基本表单'
                //         },
                //         {
                //             index: '3-2',
                //             title: '三级菜单',
                //             subs: [
                //                 {
                //                     index: 'editor',
                //                     title: '富文本编辑器'
                //                 },
                //                 {
                //                     index: 'markdown',
                //                     title: 'markdown编辑器'
                //                 }
                //             ]
                //         },
                //         {
                //             index: 'upload',
                //             title: '文件上传'
                //         }
                //     ]
                // },

                {
                    icon: 'el-icon-picture',
                    index: '4',
                    title: '人脸库管理',
                    subs: [
                        {
                            index: 'studentsFaces',
                            title: '学生人脸库'
                        },
                        {
                            index: 'teachersFaces',
                            title: '教师人脸库'
                        },
                        {
                            index: 'UploadFace',
                            title: '上传人脸'
                        },
                        {
                            index: 'UpdateFace',
                            title: '更新人脸'
                        },
                        {
                            index: 'personInfo',
                            title: '人脸信息'
                        }
                    ]
                },
                {
                    icon: 'el-icon-camera-solid',
                    index: 'photograph',
                    title: '图片拍照'
                },
                {
                    icon: 'el-icon-s-tools',
                    index: 'account',
                    title: '账户安全设置',
                    subs: [
                        {
                            index: 'changePwd',
                            title: '修改密码'
                        },
                        {
                            index: 'changePwdN',
                            title: '密保设置'
                        },
                        {
                            index: 'accountStatus',
                            title: '账户冻结'
                        }
                    ]
                },

                // {
                //     icon: 'el-icon-rank',
                //     index: '6',
                //     title: '拖拽组件',
                //     subs: [
                //         {
                //             index: 'drag',
                //             title: '拖拽列表'
                //         },
                //     ]
                // },

                {
                    icon: 'el-icon-lx-warn',
                    index: '7',
                    title: '错误处理',
                    subs: [
                        {
                            index: 'permission',
                            title: '权限测试'
                        },
                        {
                            index: '404',
                            title: '404页面'
                        }
                    ]
                },
                // {
                //     icon: 'el-icon-lx-redpacket_fill',
                //     index: '/donate',
                //     title: '支持作者'
                // }
            ]
        };
    },
    computed: {
        onRoutes() {
            return this.$route.path.replace('/', '');
        }
    },
    created() {
        //console.log(this.roseID);
        //页面渲染---角色判断---分配功能组件
        if (this.roseID === '0') {
            this.Items = this.studentsItems;
        } else if (this.roseID === '1') {
            this.Items = this.teachersItems;
        } else {
            this.Items = this.adminItems;
        }

        // 通过 Event Bus 进行组件间通信，来折叠侧边栏
        bus.$on('collapse', (msg) => {
            this.collapse = msg;
            bus.$emit('collapse-content', msg);
        });
    }
};
</script>

<style scoped>
.sidebar {
    display: block;
    position: absolute;
    left: 0;
    top: 70px;
    bottom: 0;
    overflow-y: scroll;
}
.sidebar::-webkit-scrollbar {
    width: 0;
}
.sidebar-el-menu:not(.el-menu--collapse) {
    width: 250px;
}
.sidebar > ul {
    height: 100%;
}
</style>
